//an enum for different types of physical entities
enum EntTyp {
    Stone,
    WtrPart
}

//a struct that stores all data for an entity
typedef struct {
    Vec2 pos;
    Vec2 vel;
    float mass;
    enum EntTyp kind;
} Ent;

Ent stone(float pos_i) {
    return (Ent) {
        .pos_i = pos;
        .kind = Stone;
    }
}

Ent wtr(float pos_i, float vel_i) {
    return (Ent) {
        .pos = pos_i;
        .vel = vel_i;
        .kind = Stone;
    }
}

void phys_tick(Ent& entity) {
    

    //move position by velocity
    entity.pos = add2(entity.pos, entity.vel);
}