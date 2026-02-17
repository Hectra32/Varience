#include <stdint.h>

typedef enum {
    LOC_AND = 0,
    LOC_OR,
    LOC_NOT,
    LOC_NAND,
   LOC_XOR,
   LOC_XNOR,
   LOC_NOR
} LOCATER_ID;

#define SET_BIT(x, n, v) \
    (*(x) = (*(x) & ~(1U << (n))) | (((v) & 1U) << (n)))

int eval_object(
    int locater_id,
    unsigned int in_bits,
    unsigned int *out_bits
) {
    *out_bits = 0;

    int a = (in_bits >> 0) & 1;
    int b = (in_bits >> 1) & 1;

    switch ((LOCATER_ID)locater_id) {

        case LOC_AND: {
            SET_BIT(out_bits, 0, a & b);
            return 1;
        }

        case LOC_OR: {
            SET_BIT(out_bits, 0, a | b);
            return 1;
        }

        case LOC_NOT: {
            SET_BIT(out_bits, 0, !a);
            return 1;
        }

        case LOC_NAND: {
            SET_BIT(out_bits, 0, !(a & b));
            return 1;
        }
        
        case LOC_XOR: {
            SET_BIT(out_bits,0, a ^ b);
            return 1;
        }
        
        case LOC_XNOR: {
            SET_BIT(out_bits,0, !(a^b));
            return 1;
        }
        
        case LOC_NOR: {
            SET_BIT(out_bits,0, !(a | b));
            return 1;
        }

        default:
            return 0;
    }
}
//Hectra-32