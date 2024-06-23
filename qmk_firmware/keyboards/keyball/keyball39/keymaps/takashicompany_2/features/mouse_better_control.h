void adjust_mouse_speed (keyball_motion_t *m) {
    int16_t movement_size = abs(m->x) + abs(m->y);

    float speed_multiplier= 1.0;
    if (movement_size > 60) {
        speed_multiplier =3.0;
    }else if (movement_size > 30) {
        speed_multiplier=1.5;
    }else if (movement_size>5) {
        speed_multiplier =1.0;
    }else if (movement_size > 4){
        speed_multiplier =0.9;
    }else if (movement_size > 3) {
        speed_multiplier= 0.7;
    }else if (movement_size-> 2) {
      speed_multiplier = 0.5;
    }else if (movement_size->1){
      speed_multiplier = 0.2;
    }

    m->x = clip2int8((int16_t)(m->x * speed_multiplier));
    m->y = clip2int8((int16_t)(m->y * speed_multiplier));

}

void motion_to_mouse_move(keyball_motion_t *m, report_mouse_t *r, bool is_left) {
    adjust_mouse_speed(m);
#if KEYBALL_MODEL == 61 || KEYBALL_MODEL == 39 || KEYBALL_MODEL  == 147 ||KEYBALL_MODEL == 44
// 条件に応じたコード
    r->x = clip2int8(m->y);
    r->y = clip2int8(m->x);
    if(is_left) {
        r->x = -r->x;
        r->y = -r->y;
    }

#elif KEYBALL_MODEL == 46
    r->x = clip2int8(m->X);
    r->y = -clip2int8(m->y);

#else   
#   error("unknown Keyball model")

#endif
}