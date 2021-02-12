
#ifndef COSMO_ENGINE_PLAYER_H
#define COSMO_ENGINE_PLAYER_H

#include <memory>
#include <base/Singleton.h>
#include <engine/core/CMap.h>
#include "defines.h"

extern const sint16 player_x_offset_tbl[];
extern const sint16 player_y_offset_tbl[];

//Data
extern uint16 player_death_counter;
extern int player_walk_anim_index;
extern int player_is_being_pushed_flag;
extern int player_hanging_on_wall_direction;

extern int player_direction;

extern uint16 player_sprite_dir_frame_offset;
extern int player_input_jump_related_flag;

extern int player_bounce_height_counter;
extern int player_bounce_flag_maybe;

extern int is_standing_slipry_slope_left_flg;
extern int is_standing_slipry_slope_right_flg;

extern uint8 health;
extern uint8 num_health_bars;

extern uint16 num_bombs;
extern uint16 has_had_bomb_flag;

extern int teleporter_state_maybe;
extern int player_is_teleporting_flag;
extern int teleporter_counter;

extern uint8 player_in_pneumatic_tube_flag;

extern uint16 player_invincibility_counter;

extern int player_fall_off_map_bottom_counter;

extern int num_hits_since_touching_ground;
extern uint8 show_monster_attack_hint;

extern uint8 player_has_shown_ouch_bubble_flag;
extern int player_idle_counter;
extern uint16 word_28F94;
extern int word_2E180;
extern bool hitDetectionWithPlayer;
extern int hide_player_sprite;
extern int player_spring_jump_flag;
extern int word_2E214;
extern int player_hoverboard_counter;
extern int word_32EAC;
extern int word_32EB2;

extern unsigned char byte_2E182;
extern unsigned char byte_2E2E4;

extern bool god_mode_flag;

extern bool cheat_hack_mover_enabled;

typedef enum SpeechBubbleType {
    WHOA = 0xf4,
    UMPH = 0xf5,
    POINTS_50000 = 0xf6,
    OUCH = 0xeb
} SpeechBubbleType;

#define gCosmoPlayer cosmos_engine::Player::get()

namespace cosmos_engine
{

class Player : public GsSingleton<Player>
{
public:

    void setMapPtr(std::shared_ptr<CMap> &mapPtr);


    /**
     * @brief handleInput Some input and responding logic
     */
    void handleInput();

    /**
     * @brief updateHoverboard
     */
    void updateHoverboard();

    void resetState();

    void resetWalkCycle();

    void resetPushVariables();

    void displaySprite(const int frame_num,
                       const float x_pos,
                       const float y_pos,
                       const DrawMode tile_display_func_index);

    int updateSprite();

    void loadTiles();

    void updateWalkAnim();

    int checkCollisionWithActor(const int actorInfoIndex,
                                const int frame_num,
                                int x_pos,
                                const int y_pos);

    int bounceInAir(int bounce_height);

    void addScoreForActor(int actorInfoIndex);

    void addToScore(const int amount_to_add_low);

    void decreaseHealth();

    void pushAround(int push_direction,
                    int push_anim_duration,
                    int push_duration,
                    int player_frame_num,
                    int dont_push_while_jumping_flag,
                    int check_for_blocking_flag);

    void moveOnPlatform(int platform_x_left,
                        int platform_x_right,
                        int x_offset_tbl_index,
                        int y_offset_tbl_index);

    void addSpeechBubble(const SpeechBubbleType type);


    int xPos();
    int yPos();

    void setPos(const int x, const int y);

private:

    BlockingType checkMovement(int direction, int x_pos, int y_pos);

    void push();    

    void updateIdleAnim();

    void hackMoverUpdate();

    bool mIsGrabbingWall = false;
    int mWatchingDirection = 3;

    float player_y_pos = 0.0f;
    float player_x_pos = 0.0f;

    std::shared_ptr<CMap> mpMap;
};

};

#endif //COSMO_ENGINE_PLAYER_H
