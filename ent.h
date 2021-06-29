//an enum for different types of physical entities
enum EntTyp {
    Stn,
    WtrPrt
};

//a struct that stores all data for an entity
typedef struct {
    Vec2 pos;
    Vec2 vel;
    float mass;
    enum EntTyp kind;
} Ent;

Ent stn(float pos_i) {
    return (Ent) {
        .pos = pos_i,
        .kind = Stn,
    };
}

//Client state static struct
static struct {
    /* entities */
    Ent entities[1000];
} ent;

void rndr_stn(Ent *entity) {
    draw_scale(1.0f, 1.0f);
    draw_pivot(0.2f, 0.0f);
    draw_dir(vec2(0.0f, 0.0f));
    draw_rad(0.1f);
    draw_color(0, 0, 255, 255);
    Vec2 position = mouse_pos_world(entity->pos);
    draw_pos_vec(position);
}

Ent wtr_prt(float pos_i, float vel_i) {
    return (Ent) {
        .pos = pos_i,
        .vel = vel_i,
        .kind = WtrPrt,
    };
}

void rndr_wtr_prt(Ent *entity) {
    draw_scale(1.0f, 1.0f);
    draw_pivot(0.2f, 0.0f);
    draw_dir(vec2(0.0f, 0.0f));
    draw_rad(0.1f);
    draw_color(0, 0, 255, 255);
    Vec2 position = mouse_pos_world(entity->pos);
    draw_pos_vec(position);
}

void phys_tick(Ent *entity) {
    

    //move position by velocity
    entity->pos = add2(entity->pos, entity->vel);
}

void rndr(Ent *entity) {
    draw_start();
    switch (entity->kind) {
        case Stn: rndr_stn(entity);
        case WtrPrt: rndr_wtr_prt(entity);
    }
    draw();
}