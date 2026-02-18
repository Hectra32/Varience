import pygame
import sys
import ctypes
from ctypes import c_int, POINTER, c_uint, byref
import json

pygame.init()

# ================== CONFIG ==================
WIDTH, HEIGHT = 1600, 720
GRID_X = 100
GRID_Y = 50

NODE_RADIUS = 14

# ================== WINDOW ==================
screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()
font = pygame.font.SysFont(None, 22)

# ================== COLORS ==================
BG = (22, 22, 22)
GRID_COLOR = (40, 40, 40)
PANEL_COLOR = (60, 60, 60)
TEXT_COLOR = (230, 230, 230)
GREEN = (80, 190, 110)
GREY = (64,64,64)
RED = (190, 80, 80)
NODE_IDLE = (220, 220, 220)
NODE_SELECTED = (80, 200, 200)

# ================== LOAD JSON ==================
with open("objects.json", "r") as f:
    panel_objects = json.load(f)

# ================== LOAD ASTAR ==================
lib_astar = ctypes.CDLL("/data/data/ru.iiec.pydroid3/files/libastar.so")
lib_astar.make_path.argtypes = [
    c_int, c_int,
    c_int, c_int,
    POINTER(c_int)
]
lib_astar.make_path.restype = c_int

MAX_POINTS = 1024
path_buffer = (c_int * (MAX_POINTS * 2))()

# ================== LOAD LOGIC ==================
#CHANGE FILE PATH ACCORDING TO YOUR USE 
lib_logic = ctypes.CDLL("/data/data/ru.iiec.pydroid3/files/liblogic.so")
lib_logic.eval_object.argtypes = [
    c_int,
    c_uint,
    POINTER(c_uint)
]
lib_logic.eval_object.restype = c_int

# ================== LOCATER ENUM ==================
LOC_AND  = 0
LOC_OR   = 1
LOC_NOT  = 2
LOC_NAND = 3
LOC_XOR = 4
LOC_XNOR =5
LOC_NOR =6

LOCATER_MAP = {
    "AND":  LOC_AND,
    "OR":   LOC_OR,
    "NOT":  LOC_NOT,
    "NAND": LOC_NAND,
    "XOR": LOC_XOR,
    "XNOR": LOC_XNOR,
    "NOR": LOC_NOR
}
#NON USED IT HAS BEEN DEFINED IN JSON ALREADY 


# ================== PANEL ==================
panel_width = 500
panel = pygame.Rect(-panel_width, 0, panel_width, HEIGHT)
panel_hidden_x = -panel_width
panel_shown_x = -1
panel_speed = 20
menu_open = False

CELL_W = panel_width // 2
CELL_H = HEIGHT // 2

# ================== BUTTONS ==================
button_radius = 28
button_y = 40
GAP = 30

DELETE_BTN_RADIUS = 28
DELETE_BTN_OFFSET_Y = 80
delete_mode = False

# ================== STORAGE ==================
spawned_objects = []
panel_item_rects = []
spawn_offset = 0
SPAWN_STEP = 20
current_drag = None
object_id_counter = 0
paths_refs = []

# ================== FUNCTIONS ==================
def get_side_nodes(rect, count, side):
    nodes = []
    if count <= 0:
        return nodes
    gap = rect.height / (count + 1)
    for i in range(count):
        y = rect.top + gap * (i + 1)
        x = rect.left if side == "left" else rect.right
        nodes.append((int(x), int(y)))
    return nodes

def get_object_by_id(oid):
    for obj in spawned_objects:
        if obj["id"] == oid:
            return obj
    return None

def get_node_pos(obj_id, node_index):
    obj = get_object_by_id(obj_id)
    if not obj:
        return None
    if node_index >= len(obj["nodes"]):
        return None
    return obj["nodes"][node_index]["pos"]

def get_selected_node_refs():
    refs = []
    for obj in spawned_objects:
        for node in obj["nodes"]:
            if node["selected"]:
                refs.append((obj["id"], node["index"]))
    return refs

def eval_gate(locater_id, in_bits):
    out_bits = c_uint(0)
    n_out = lib_logic.eval_object(
        c_int(locater_id),
        c_uint(in_bits),
        byref(out_bits)
    )
    return n_out, out_bits.value
    
print("panel_objects type:", type(panel_objects))
print("Are they same object?", spawned_objects is panel_objects)
# ====================== MAIN LOOP ======================
while True:

    button_x = panel.right + GAP
    delete_btn_x = button_x
    delete_btn_y = button_y + DELETE_BTN_OFFSET_Y

    # ================= INPUT =================
    for event in pygame.event.get():

        # -------- QUIT --------
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

        # -------- MOUSE DOWN --------
        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            mx, my = event.pos

            # Toggle menu
            if (mx - button_x)**2 + (my - button_y)**2 <= button_radius**2:
                menu_open = not menu_open
                continue

            # Toggle delete
            if not menu_open:
                if (mx - delete_btn_x)**2 + (my - delete_btn_y)**2 <= DELETE_BTN_RADIUS**2:
                    delete_mode = not delete_mode
                    continue

            # -------- SPAWN --------
            if menu_open:
                for item in panel_item_rects:
                    if item["rect"].collidepoint(mx, my):

                        src = item["data"]
                        w, h = src["size"]

                        rect = pygame.Rect(
                            WIDTH//2 - w//2 + spawn_offset,
                            HEIGHT//2 - h//2 + spawn_offset,
                            w, h
                        )

                        spawn_offset += SPAWN_STEP

                        nodes = []

                        # Inputs
                        for p in get_side_nodes(rect, src.get("inputs", 0), "left"):
                            nodes.append({
                                "pos": p,
                                "selected": False,
                                "signal": 0,
                                "type": "input"
                            })

                        # Outputs
                        for p in get_side_nodes(rect, src.get("outputs", 0), "right"):
                            nodes.append({
                                "pos": p,
                                "selected": False,
                                "signal": 0,
                                "type": "output"
                            })
                        assert hasattr(event, "pos"), f"Event has no pos: {event} ({type(event)})"
                        assert isinstance(event.pos, (tuple, list)), f"event.pos is wrong type: {type(event.pos)}"


                        for i, n in enumerate(nodes):
                            n["index"] = i

                        if src["locater"] == "INPUT":
                            spawned_objects.append({
                                "id": object_id_counter,
                                "rect": rect,
                                "color": src["color"],
                                "name": src["name"],
                                "type": "source",
                                "value": 0,
                                "nodes": nodes,
                                "output_bits": 0,
                                "dragging": False,
                                "offset": (0, 0)
                            })
                        else:
                            loc_id = src["locater"]
                            print("hh")
                            spawned_objects.append({
                                "id": object_id_counter,
                                "rect": rect,
                                "color": src["color"],
                                "name": src["name"],
                                "type": "gate",
                                "locater_id": loc_id,
                                "nodes": nodes,
                                "output_bits": 0,
                                "dragging": False,
                                "offset": (0, 0)
                            })
                        
                        object_id_counter += 1
                        clicked_node = False
                        current_drag = None
                        continue
                        break
                continue

            #---------INPUT TOGGLE NODE--------

            # -------- NODE CLICKING --------
            clicked_node = False

            for obj in spawned_objects:
                for node in obj["nodes"]:
                    nx, ny = node["pos"]
                    if (mx - nx)**2 + (my - ny)**2 <= NODE_RADIUS**2:
                        node["selected"] = not node["selected"]
                        clicked_node = True
                        break
                if clicked_node:
                    break

            if clicked_node:
                refs = get_selected_node_refs()
                if len(refs) == 2:
                    obj1 = get_object_by_id(refs[0][0])
                    obj2 = get_object_by_id(refs[1][0])

                    node1 = obj1["nodes"][refs[0][1]]
                    node2 = obj2["nodes"][refs[1][1]]

                    if node1["type"] == "output" and node2["type"] == "input":
                        paths_refs.append({"from": refs[0], "to": refs[1]})
                    elif node2["type"] == "output" and node1["type"] == "input":
                        paths_refs.append({"from": refs[1], "to": refs[0]})

                    for o in spawned_objects:
                        for n in o["nodes"]:
                            n["selected"] = False

                continue

            # -------- OBJECT CLICK --------
            for obj in reversed(spawned_objects):
                if obj["rect"].collidepoint(mx, my):

                    # DELETE MODE
                    if delete_mode:
                        deleted_id = obj["id"]
                        spawned_objects.remove(obj)

                        paths_refs = [
                            p for p in paths_refs
                            if p["from"][0] != deleted_id and p["to"][0] != deleted_id
                        ]
                        break
                        
                    print("SPAWNED OBJECTS SNAPSHOT:")
                    for i, o in enumerate(spawned_objects):
                        print(i, type(o), o.keys() if isinstance(o, dict) else o)

                    # START DRAG
                    current_drag = obj
                    obj["dragging"] = True
                    ox = mx - obj["rect"].x
                    oy = my - obj["rect"].y
                    obj["offset"] = (ox, oy)
                    break

        # -------- DRAGGING --------
        if event.type == pygame.MOUSEMOTION:
            if current_drag:
                mx, my = event.pos
                ox, oy = current_drag["offset"]

                old_x = current_drag["rect"].x
                old_y = current_drag["rect"].y

                current_drag["rect"].x = mx - ox
                current_drag["rect"].y = my - oy

                dx = current_drag["rect"].x - old_x
                dy = current_drag["rect"].y - old_y

                for node in current_drag["nodes"]:
                    x, y = node["pos"]
                    node["pos"] = (x + dx, y + dy)

        # -------- STOP DRAG --------
        if event.type == pygame.MOUSEBUTTONUP:
            if current_drag:
                current_drag["dragging"] = False
                current_drag = None

    # ================= UPDATE =================

    # Slide panel animation
    target_x = panel_shown_x if menu_open else panel_hidden_x
    panel.x += (target_x - panel.x) * 0.2

    # Reset input nodes
    for obj in spawned_objects:
        for node in obj["nodes"]:
            if node["type"] == "input":
                node["signal"] = 0

    # Propagate connections
    for pref in paths_refs:
        from_obj = get_object_by_id(pref["from"][0])
        to_obj   = get_object_by_id(pref["to"][0])
        if not from_obj or not to_obj:
            continue

        from_node = from_obj["nodes"][pref["from"][1]]
        to_node   = to_obj["nodes"][pref["to"][1]]

        if from_node["type"] == "output" and to_node["type"] == "input":
            to_node["signal"] = from_node["signal"]

    # Evaluate objects
    for obj in spawned_objects:

        if obj.get("type") == "source":
            for node in obj["nodes"]:
                if node["type"] == "output":
                    node["signal"] = obj["value"]
            continue

        input_nodes = [n for n in obj["nodes"] if n["type"] == "input"]
        output_nodes = [n for n in obj["nodes"] if n["type"] == "output"]

        in_bits = 0
        for i, node in enumerate(input_nodes):
            if node["signal"]:
                in_bits |= (1 << i)

        n_out, out_bits = eval_gate(obj["locater_id"], in_bits)

        for i, node in enumerate(output_nodes):
            node["signal"] = (out_bits >> i) & 1
            

    # ================= DRAW =================
    screen.fill(BG)

    for x in range(0, WIDTH, GRID_X):
        pygame.draw.line(screen, GRID_COLOR, (x,0), (x,HEIGHT))
    for y in range(0, HEIGHT, GRID_Y):
        pygame.draw.line(screen, GRID_COLOR, (0,y), (WIDTH,y))

    # Draw paths
    for pref in paths_refs:
        p1 = get_node_pos(pref["from"][0], pref["from"][1])
        p2 = get_node_pos(pref["to"][0], pref["to"][1])
        if not p1 or not p2:
            continue

        x1, y1 = p1
        x2, y2 = p2

        cnt = lib_astar.make_path(x1, y1, x2, y2, path_buffer)

        from_obj = get_object_by_id(pref["from"][0])
        signal = from_obj["nodes"][pref["from"][1]]["signal"]
        color = (255,0,0) if signal else (255,255,255)

        for i in range(cnt-1):
            pygame.draw.line(
                screen,
                color,
                (path_buffer[i*2], path_buffer[i*2+1]),
                (path_buffer[(i+1)*2], path_buffer[(i+1)*2+1]),
                5
            )

    # Draw objects
    for obj in spawned_objects:
        pygame.draw.rect(screen, obj["color"], obj["rect"])
        label = font.render(obj["name"], True, TEXT_COLOR)
        screen.blit(label, label.get_rect(center=obj["rect"].center))

        for node in obj["nodes"]:
            NODE_COLOUR = (200,0,0) if node["signal"] else NODE_IDLE
            pygame.draw.circle(screen, NODE_COLOUR, node["pos"], NODE_RADIUS)
        
    
    
    # Panel
    pygame.draw.rect(screen, PANEL_COLOR, panel)
    panel_item_rects.clear()

    if menu_open:
        cols = 2
        total = len(panel_objects)
        rows = (total + cols - 1) // cols

        cell_w = panel.width // cols
        cell_h = HEIGHT // max(rows, 1)

        for i, obj in enumerate(panel_objects):
            row = i // cols
            col = i % cols

            w, h = obj["size"]

            x = panel.x + col * cell_w + (cell_w - w) // 2
            y = row * cell_h + (cell_h - h) // 2

            rect = pygame.Rect(x, y, w, h)

            panel_item_rects.append({
                "rect": rect,
                "data": obj
            })

            pygame.draw.rect(screen, obj["color"], rect)
            label = font.render(obj["name"], True, TEXT_COLOR)
            screen.blit(label, label.get_rect(center=rect.center))

    pygame.draw.circle(screen, GREEN, (button_x, button_y), button_radius)

    if not menu_open:
        pygame.draw.circle(
            screen,
            RED if delete_mode else GREY,
            (delete_btn_x, delete_btn_y),
            DELETE_BTN_RADIUS
        )

    pygame.display.flip()
    clock.tick(60)