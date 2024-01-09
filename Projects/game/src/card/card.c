#include "card.h"

int card_data_to_number(card_data data) {
    int final = 0;
    final += (data.type * 13);
    final += data.value;
    return final;
}