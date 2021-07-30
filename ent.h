#define MAX_ENTITIES 10000
#define BOUNDS 1.0

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
    float rot;
    float spin;
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

/* water functions */
Ent wtr_prt(Vec2 pos_i, Vec2 vel_i) {
    return (Ent) {
        .pos = pos_i,
        .vel = vel_i,
        .kind = WtrPrt,
    };
}

void add_ent(Ent entity) {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (ent.entities[i].kind == None) {
            ent.entities[i] = entity;
            return;
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
            break;
        case Stn: 
            /* collisions */

            

            /* physics */

            //gravity
            entity->vel.y = entity->vel.y - 0.0001f;

            //rotate direction by spin
            entity->rot = entity->rot + entity->spin;

            //move position by velocity
            entity->pos = add2(entity->pos, entity->vel);
            break;
        case WtrPrt: 
            //gravity
            entity->vel.y = entity->vel.y - 0.0001f;

            /* collisions */

            //set vertical velocity to zero if hitting bottom of world
            if (add2(entity->pos, entity->vel).y < -5.5) {
                entity->vel.y = 0;
            }

            //move position by velocity
            entity->pos = add2(entity->pos, entity->vel);
            break;
    }
}

void tick_all_ents() {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        tick(&ent.entities[i]);
    }
}

void rndr(Ent *entity) {
    if (entity->kind == None) {
        //return if the entity is a none
        return;
    }
    draw_start();
    switch (entity->kind) {
        case None:
            /* do nothing if the entity is a none */;
        break;
        case Stn: 
            draw_scale(1.0f, 1.0f);
            draw_rad(0.1f);
            draw_color(0, 0, 0, 128);
            draw_pos_vec(entity->pos);
            break;
        case WtrPrt: 
            draw_scale(0.1f, 0.1f);
            draw_rot(entity->rot);
            draw_rad(0.5f);
            draw_color(0, 0, 255, 255);
            draw_pos_vec(entity->pos);
            //printf("water particle rendering!");
            break;
    }
    draw();
}

void rndr_all_ents() {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        rndr(&ent.entities[i]);
    }
}
