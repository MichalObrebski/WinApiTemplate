#include "board.h"

board::board() : m_fields{}{
    recalculate_fields(width, height);
}
void board::recalculate_fields(int new_width, int new_height){
    int field_width = field_size * ((double)new_width/(double)width);
    int field_height = field_size * ((double)new_height/(double)height);
    for(LONG i = 0; i < rows; i++)
    for(LONG j = 0; j < cols; j++){
        auto &f = m_fields[i * rows +j];
        f.position.top = i * field_height + 5 * i;
        f.position.left = j * field_width + 5 * j;
        f.position.bottom = f.position.top + field_height;
        f.position.right = f.position.left + field_width;
    }
}