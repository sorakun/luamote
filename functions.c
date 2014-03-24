#include "wiic.h"

#include "lua/lua.h"
#include "lua/lauxlib.h"


/* main api */

static int wiiInit(lua_State *L)
{
    int x = atoi(lua_tostring(L, 1));

    lua_pushlightuserdata(L, wiic_init(x));
    return 1;
}

static int wiiFind(lua_State *L)
{
    wiimote **wm = lua_touserdata(L, 1);
    printf("WM = %d\n", wm);
    int max = atoi(lua_tostring(L, 2));
    int delay = atoi(lua_tostring(L, 3));

    lua_pushinteger(L,  wiic_find(wm, max, delay));
    return 1;
}

static int wiiConnect(lua_State *L)
{
    wiimote **wm = lua_touserdata(L, 1);
    int max = atoi(lua_tostring(L, 2));

    lua_pushinteger(L, wiic_connect(wm, max));
    return 1;
}

static int wiiGetMote(lua_State *L)
{
    wiimote **wm = lua_touserdata(L, 1);
    int idx = atoi(lua_tostring(L, 2));

    lua_pushlightuserdata(L, wm[idx]);
    return 1;
}

static int wiiSetLed(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);
    int led = atoi(lua_tostring(L, 2));

    wiic_set_leds(wm, led);
    return 1;
}

static int wiiRumble(lua_State *L)
{
    wiimote **wm = lua_touserdata(L, 1);
    int status = atoi(lua_tostring(L, 2));

    wiic_rumble(wm, status);
    return 1;
}

static int wiiCleanUp(lua_State *L)
{
    wiimote **wm = lua_touserdata(L, 1);
    int count = atoi(lua_tostring(L, 2));

    wiic_cleanup(wm, count);
    return 1;
}

static int wiiToggleRumble(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);

    wiic_toggle_rumble(wm);
    return 1;
}

static int wiiMotionSensing(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);
    int status = atoi(lua_tostring(L, 2));

    wiic_motion_sensing(wm, status);
    return 1;
}

static int wiiDisconnect(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);

    wiic_disconnect(wm);
    return 1;
}

static int wiiStatus(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);

    wiic_status(wm);
    return 1;
}

static int wiiSetOrientThreshold(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);
    double value = atof(lua_tostring(L, 2));

    wiic_set_orient_threshold(wm, value);
    return 1;
}

static int wiiSetAccelThreshold(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);
    int value = atoi(lua_tostring(L, 3));

    wiic_set_accel_threshold(wm, value);
    return 1;
}

static int wiiResync(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);

    wiic_resync(wm);
    return 1;
}

static int wiiPoll(lua_State *L)
{
    wiimote **wm = lua_touserdata(L, 1);
    int count = atoi(lua_tostring(L, 2));

    lua_pushinteger(L, wiic_poll(wm, count));
    return 1;
}

// TODO
static int wiiReadData(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);
    byte  buffer[50];
    int addr = atoi(lua_tostring(L, 2));
    short len = atoi(lua_tostring(L, 3));

    lua_pushinteger(L, wiic_read_data(wm, buffer, addr, len));
    lua_pushstring(L, buffer);
    return 1;
}

static int wiiWriteData(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);
    byte  buffer[50];
    int addr = atoi(lua_tostring(L, 2));
    byte * data = lua_tostring(L, 3);
    int len = atoi(lua_tostring(L, 4));

    lua_pushinteger(L, wiic_write_data(wm, addr, data, len));
    return 1;
}

static int wiiSetFlags(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);
    int enable = atoi(lua_tostring(L, 2));
    int disable = atoi(lua_tostring(L, 3));

    lua_pushinteger(L, wiic_set_flags(wm, enable, disable));
    return 1;
}

static int wiiSetSmoothAlpha(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);
    double alpha = atof(lua_tostring(L, 2));

    lua_pushnumber(L, wiic_set_smooth_alpha(wm, alpha));
    return 1;
}

void wiiSetNunchukOrientThreshold(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);
    double threshold = atof(lua_tostring(L, 2));

    wiic_set_nunchuk_orient_threshold(wm, threshold);
    return 1;
}

void wiiSetNunchukAccelThreshold(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);
    int threshold = atoi(lua_tostring(L, 2));

    wiic_set_nunchuk_accel_threshold(wm, threshold);
    return 1;
}

void wiiSetIR(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);
    int status = atoi(lua_tostring(L, 2));
    //printf("done\n");
    wiic_set_ir(wm, status);
    printf("IR Updated.");
    return 1;
}

static int wiiSetIRVres(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);
    int x = atoi(lua_tostring(L, 2));
    int y = atoi(lua_tostring(L, 3));

    wiic_set_ir_vres(wm, x, y);
    return 1;
}

static int wiiSetIRPosition(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);
    int pos = atoi(lua_tostring(L, 2));

    if (pos == 0)
        wiic_set_ir_position(wm, WIIC_IR_ABOVE);
    else
        wiic_set_ir_position(wm, WIIC_IR_BELOW);

    return 1;
}

static int wiiSetIRSensitivity(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);
    int sensitivity = atoi(lua_tostring(L, 2));

    wiic_set_ir_sensitivity(wm, sensitivity);
    return 1;
}

static int wiiSetAspectRatio(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);
    int aspect = atoi(lua_tostring(L, 2));

    if (aspect == 0)
        wiic_set_aspect_ratio(wm, WIIC_ASPECT_4_3);
    else
        wiic_set_aspect_ratio(wm, WIIC_ASPECT_16_9);

    return 1;
}

/* utilities */

/* get the event type of a given wiimote */
static int wiiGetEvent(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);

    switch(wm->event)
    {
        case WIIC_NONE:
            lua_pushinteger(L, 0);
            break;
        case WIIC_EVENT:
            lua_pushinteger(L, 1);
            break;
        case WIIC_STATUS:
            lua_pushinteger(L, 2);
            break;
        case WIIC_CONNECT:
            lua_pushinteger(L, 3);
            break;
        case WIIC_DISCONNECT:
            lua_pushinteger(L, 4);
            break;
        case WIIC_UNEXPECTED_DISCONNECT:
            lua_pushinteger(L, 5);
            break;
        case WIIC_READ_DATA:
            lua_pushinteger(L, 6);
            break;
        case WIIC_NUNCHUK_INSERTED:
            lua_pushinteger(L, 7);
            break;
        case WIIC_NUNCHUK_REMOVED:
            lua_pushinteger(L, 8);
            break;
        case WIIC_CLASSIC_CTRL_INSERTED:
            lua_pushinteger(L, 9);
            break;
        case WIIC_CLASSIC_CTRL_REMOVED:
            lua_pushinteger(L, 10);
            break;
        case WIIC_GUITAR_HERO_3_CTRL_INSERTED:
            lua_pushinteger(L, 11);
            break;
        case WIIC_GUITAR_HERO_3_CTRL_REMOVED:
            lua_pushinteger(L, 12);
            break;
    }

    return 1;
}

static int wiiGetId(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);

    lua_pushinteger(L, wm->unid);
    return 1;
}

static int wiiIsPressed(lua_State *L)
{
    /* can be applied to a wii mote or any extention */
    wiimote *thing = lua_touserdata(L, 1);
    int key = atoi(lua_tostring(L, 2));

    lua_pushboolean(L, IS_PRESSED(thing, key));
    return 1;
}

static int wiiIsJustPressed(lua_State *L)
{
    /* can be applied to a wii mote or any extention */
    wiimote *thing = lua_touserdata(L, 1);
    int key = atoi(lua_tostring(L, 2));

    lua_pushboolean(L, IS_JUST_PRESSED(thing, key));
    return 1;
}

static int wiiReleased(lua_State *L)
{
    /* can be applied to a wii mote or any extention */
    wiimote *thing = lua_touserdata(L, 1);
    int key = atoi(lua_tostring(L, 2));

    lua_pushboolean(L, IS_RELEASED(thing, key));
    return 1;
}

static int wiiIsHeld(lua_State *L)
{
    /* can be applied to a wii mote or any extention */
    wiimote *thing = lua_touserdata(L, 1);
    int key = atoi(lua_tostring(L, 2));

    lua_pushboolean(L, IS_HELD(thing, key));
    return 1;
}

static int wiiGetRPY(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);

    lua_newtable(L);

    lua_pushstring(L, "roll");
    lua_pushnumber(L, wm->orient.roll);
    lua_settable(L, -3);

    lua_pushstring(L, "pitch");
    lua_pushnumber(L, wm->orient.pitch);
    lua_settable(L, -3);

    lua_pushstring(L, "yaw");
    lua_pushnumber(L, wm->orient.yaw);
    lua_settable(L, -3);

    return 1;
}

static int wiiGetIRPosition(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);

    lua_newtable(L);
    lua_pushstring(L, "x");
    lua_pushinteger(L, wm->ir.ax);
    lua_settable(L, -3);
    lua_pushstring(L, "y");
    lua_pushinteger(L, wm->ir.ay);
    lua_settable(L, -3);
    lua_pushstring(L, "z");
    lua_pushinteger(L, wm->ir.z);
    lua_settable(L, -3);

    return 1;
}

/* TODO work on attached devices */

static int wiiGetAttachedDevice(lua_State *L)
{
    wiimote *wm = lua_touserdata(L, 1);
    /* device id */
    int d_id = atoi(lua_tostring(L, 2));
    switch (d_id)
    {
        case EXP_NONE:
            lua_pushlightuserdata(L, 0);
            break;
        case EXP_NUNCHUK:
            lua_pushlightuserdata(L, &wm->exp.nunchuk);
            break;
        case EXP_CLASSIC:
            lua_pushlightuserdata(L, &wm->exp.classic);
            break;
        case EXP_GUITAR_HERO_3:
            lua_pushlightuserdata(L, &wm->exp.gh3);
            break;
        case EXP_MOTION_PLUS:
            lua_pushlightuserdata(L, &wm->exp.mp);
            break;
        case EXP_BALANCE_BOARD:
            lua_pushlightuserdata(L, &wm->exp.bb);

    }
    return 1;
}

int luaopen_libwii (lua_State *L)
{
    struct luaL_Reg driver[] =
    {
        {"init", wiiInit},
        {"cleanup", wiiCleanUp},

        {"find", wiiFind},
        {"connect", wiiConnect},
        {"disconnect", wiiDisconnect},
        {"getMote", wiiGetMote},

        {"poll", wiiPoll},

        {"rumble", wiiRumble},
        {"toggleRumble", wiiToggleRumble},
        {"setLed", wiiSetLed},
        {"motionSensing", wiiMotionSensing},
        {"readData", wiiReadData},
        {"writeData", wiiWriteData},
        {"status", wiiStatus},
        {"setFlags", wiiSetFlags},
        {"setSmoothAlpha", wiiSetSmoothAlpha},
        {"setOrientThreshold", wiiSetOrientThreshold},
        {"setAccelThreshold", wiiSetAccelThreshold},
        {"setNunchukOrientThreshold", wiiSetNunchukOrientThreshold},
        {"setNunchukAccelThreshold", wiiSetNunchukAccelThreshold},
        {"resync", wiiResync},

        {"setIR", wiiSetIR},
        {"setIRVres", wiiSetIRVres},
        {"setIRPosition", wiiSetIRPosition},
        {"setIRSensitivity", wiiSetIRSensitivity},
        {"setAspectRatio", wiiSetAspectRatio},

        {"getEvent", wiiGetEvent},
        {"getId", wiiGetId},
        {"pressed", wiiIsPressed},
        {"justPressed", wiiIsJustPressed},
        {"released", wiiReleased},
        {"held", wiiIsHeld},

        {"getRPY", wiiGetRPY},
        {"getIRPosition", wiiGetIRPosition},

        {NULL, NULL}
    };
    luaL_openlib(L, "libwii", driver, 0);
    return 1;
}

