#define MAX_ENTITIES 1000

//an enum for different types of physical entities
enum EntTyp {
    None,
    Stn,
    WtrPrt
};

//a struct that stores all data for an entity
typedef struct {
    Vec2 pos;
    Vec2 vel;
    Vec2 dir;
    float mass;
    void *tethers[8];
    enum EntTyp kind;
} Ent;

//Client state static struct
static struct {
    /* entities */
    Ent entities[MAX_ENTITIES];
} ent;

Ent none() {
    return (Ent) {
        .kind = None
    };
}

/* stone functions */
Ent stn(Vec2 pos_i) {
    return (Ent) {
        .pos = pos_i,
        .kind = Stn,
    };
}

void rndr_stn(Ent *entity) {
    draw_scale(1.0f, 1.0f);
    draw_dir(entity->dir);
    draw_rad(0.0f);
    draw_color(0, 0, 255, 255);
    Vec2 position = entity->pos;
    draw_pos_vec(position);
}

void tick_stn(Ent *entity) {
    //gravity
    entity->vel.y = entity->vel.y - 0.002f;

    //spinnies
    //entity->dir.x = entity->dir.x + 0.3f;
    entity->dir = vec2_rot(rot_vec2(entity->dir) + 0.1);

    //move position by velocity
    entity->pos = add2(entity->pos, entity->vel);
}

/* water functions */
Ent wtr_prt(float pos_i, float vel_i) {
    return (Ent) {
        .pos = pos_i,
        .vel = vel_i,
        .kind = WtrPrt,
    };
}

void rndr_wtr_prt(Ent *entity) {
    draw_scale(1.0f, 1.0f);
    draw_dir(entity->dir);
    draw_rad(0.1f);
    draw_color(0, 0, 255, 255);
    Vec2 position = entity->pos;
    draw_pos_vec(position);
}

void tick_wtr_prt(Ent *entity) {
    //move position by velocity
    entity->pos = add2(entity->pos, entity->vel);
}

void add_ent(Ent entity) {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (ent.entities[i].kind != None) {
            ent.entities[i] = entity;
        }
    }
}

void rm_ent(int i) {
    ent.entities[i].kind = None;
}

void tick(Ent *entity) {
    switch (entity->kind) {
        case None:
            /* do nothing if the entity is a none */;
        case Stn: 
            tick_stn(entity);
        case WtrPrt: 
            tick_wtr_prt(entity);
    }
}

void tick_all_ents() {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        tick(&ent.entities[i]);
    }
}

void rndr(Ent *entity) {
    draw_start();
    switch (entity->kind) {
        case None: 
            /* do nothing if the entity is a none */;
        case Stn: 
            rndr_stn(entity);
        case WtrPrt: 
            rndr_wtr_prt(entity);
    }
    draw();
}

void rndr_all_ents() {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        rndr(&ent.entities[i]);
    }
}