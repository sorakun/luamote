--[[
Author:
	
	C. Soulaymen 
		http://sora.eliteheberg.fr
		soulaymenc@yahoo.com

special thanks to:

	katlogic: katlogic@katsystems.eu
]] 

bit = require("bit")

local libwii = require("libwii")

wii = {	
	--[[ Constants ]]

	WIIMOTE_LED_NONE				= 0x00,
	WIIMOTE_LED_1					= 0x10,
	WIIMOTE_LED_2					= 0x20,
	WIIMOTE_LED_3					= 0x40,
	WIIMOTE_LED_4					= 0x80,

	-- button codes
	WIIMOTE_BUTTON_TWO				= 0x0001,
	WIIMOTE_BUTTON_ONE				= 0x0002,
	WIIMOTE_BUTTON_B				= 0x0004,
	WIIMOTE_BUTTON_A				= 0x0008,
	WIIMOTE_BUTTON_MINUS			= 0x0010,
	WIIMOTE_BUTTON_ZACCEL_BIT6		= 0x0020,
	WIIMOTE_BUTTON_ZACCEL_BIT7		= 0x0040,
	WIIMOTE_BUTTON_HOME				= 0x0080,
	WIIMOTE_BUTTON_LEFT				= 0x0100,
	WIIMOTE_BUTTON_RIGHT			= 0x0200,
	WIIMOTE_BUTTON_DOWN				= 0x0400,
	WIIMOTE_BUTTON_UP				= 0x0800,
	WIIMOTE_BUTTON_PLUS				= 0x1000,
	WIIMOTE_BUTTON_ZACCEL_BIT4		= 0x2000,
	WIIMOTE_BUTTON_ZACCEL_BIT5		= 0x4000,
	WIIMOTE_BUTTON_UNKNOWN			= 0x8000,
	WIIMOTE_BUTTON_ALL				= 0x1F9F,

	-- nunchul button codes
	NUNCHUK_BUTTON_Z				= 0x01,
	NUNCHUK_BUTTON_C				= 0x02,
	NUNCHUK_BUTTON_ALL				= 0x03,

	-- classic controller button codes 
	CLASSIC_CTRL_BUTTON_UP			= 0x0001,
	CLASSIC_CTRL_BUTTON_LEFT		= 0x0002,
	CLASSIC_CTRL_BUTTON_ZR			= 0x0004,
	CLASSIC_CTRL_BUTTON_X			= 0x0008,
	CLASSIC_CTRL_BUTTON_A			= 0x0010,
	CLASSIC_CTRL_BUTTON_Y			= 0x0020,
	CLASSIC_CTRL_BUTTON_B			= 0x0040,
	CLASSIC_CTRL_BUTTON_ZL			= 0x0080,
	CLASSIC_CTRL_BUTTON_FULL_R		= 0x0200,
	CLASSIC_CTRL_BUTTON_PLUS		= 0x0400,
	CLASSIC_CTRL_BUTTON_HOME		= 0x0800,
	CLASSIC_CTRL_BUTTON_MINUS		= 0x1000,
	CLASSIC_CTRL_BUTTON_FULL_L		= 0x2000,
	CLASSIC_CTRL_BUTTON_DOWN		= 0x4000,
	CLASSIC_CTRL_BUTTON_RIGHT		= 0x8000,
	CLASSIC_CTRL_BUTTON_ALL			= 0xFEFF,

	-- guitar hero 3 button codes */
	GUITAR_HERO_3_BUTTON_STRUM_UP	= 0x0001,
	GUITAR_HERO_3_BUTTON_YELLOW		= 0x0008,
	GUITAR_HERO_3_BUTTON_GREEN		= 0x0010,
	GUITAR_HERO_3_BUTTON_BLUE		= 0x0020,
	GUITAR_HERO_3_BUTTON_RED		= 0x0040,
	GUITAR_HERO_3_BUTTON_ORANGE		= 0x0080,
	GUITAR_HERO_3_BUTTON_PLUS		= 0x0400,
	GUITAR_HERO_3_BUTTON_MINUS		= 0x1000,
	GUITAR_HERO_3_BUTTON_STRUM_DOWN	= 0x4000,
	GUITAR_HERO_3_BUTTON_ALL		= 0xFEFF,


	-- wiimote option flags
	WII_SMOOTHING				= 0x01,
	WII_CONTINUOUS				= 0x02,
	WII_ORIENT_THRESH			= 0x04,
	WII_INIT_FLAGS				= 0 ,

	WII_ORIENT_PRECISION			= 100.0,

	-- expansion codes q
	EXP_NONE						= 0,
	EXP_NUNCHUK						= 1,
	EXP_CLASSIC						= 2,
	EXP_GUITAR_HERO_3				= 3,
	EXP_MOTION_PLUS 				= 4,
	EXP_BALANCE_BOARD				= 5,

	WII_IR_ABOVE = 0,
	WII_IR_BELOW = 1,

	-- aspect ratio
	WII_ASPECT_4_3 = 0,
	WII_ASPECT_16_9 = 1,

	WII_NONE = 0,
	WII_EVENT = 1,
	WII_STATUS = 2,
	WII_CONNECT = 3,
	WII_DISCONNECT = 4,
	WII_UNEXPECTED_DISCONNECT = 5,
	WII_READ_DATA = 6,
	WII_NUNCHUK_INSERTED = 7,
	WII_NUNCHUK_REMOVED = 8,
	WII_CLASSIC_CTRL_INSERTED = 9,
	WII_CLASSIC_CTRL_REMOVED = 10,
	WII_GUITAR_HERO_3_CTRL_INSERTED = 11,
	WII_GUITAR_HERO_3_CTRL_REMOVED = 12,

	-- rumble & sensing
	ON = 1,
	OFF = 0,

	max = 0,
	connected = 0, -- connected wiimotes
	addr = nil,
}

wii.WII_INIT_FLAGS = bit.bxor(wii.WII_SMOOTHING, wii.WII_ORIENT_THRESH)

function wii.init(count)
	wii.max = count
	wii.addr = libwii.init( count )
end

function wii.find(count, delay)

	return libwii.find(wii.addr, count, delay)
end

function wii.connect(count)
	wii.connected = libwii.connect(wii.addr, count)
	return wii.connected
end

function wii.getMote(idx)
	return libwii.getMote(wii.addr, idx)
end

function wii.poll(count)
	return libwii.poll(wii.addr, count)
end

-- Wiimote

Wiimote = {}

function Wiimote:new(addr)
	local obj = {
		addr = nil,
	}
	obj.addr = addr

	setmetatable(obj, { __index = Wiimote })
	return obj
end

function Wiimote:rumble(status)
	libwii.rumble(self.addr, status)
end

function Wiimote:toggleRumble()
	libwii.toggleRumble(self.addr)
end

function Wiimote:setLed(led)
	libwii.setLed(self.addr, led)
end

function Wiimote:setMotionSensing(status)
	libwii.motionSensing(self.addr, status)
end 

function Wiimote:readData(address, len)
	local success, data = libwii.readData(self.addr)
	return success, data 
end

function Wiimote:writeData(address, data, len)
	return libwii.writeData(self.addr, address, data, len)
end

function Wiimote:requestStatus()
	return libwii.status(self.addr)
end

function Wiimote:setFlags(enable, disable)
	return libwii.setFlags(self.addr, enable, disable)
end

function Wiimote:setSmoothAlpha(value)
	return 	libwii.setSmoothAlpha(self.addr, value)
end

function Wiimote:setOrientThreshold( value )
	libwii.setOrientThreshold(self.addr, value)
end

function Wiimote:setAccelThreshold( value )
	libwii.setAccelThreshold(self.addr, value)
end

function Wiimote:setNunchukOrientThreshold( value )
	libwii.setNunchukOrientThreshold(self.addr, value)
end

function Wiimote:setNunchukThreshold( value )
	libwii.setNunchukAccelThreshold(self.addr, value)
end

function Wiimote:resync()
	libwii.resync(self.addr)
end

function Wiimote:setIR( status )
	libwii.setIR(self.addr, status)
end

function Wiimote:setIRVres( x, y )
	libwii.setIRVres(self.addr, x, y)
end

function Wiimote:setIRPosition( pos )
	libwii.setIRPosition(self.addr, pos)
end

function Wiimote:setIRSensitivity( sensitivity )
	libwii.setIRSensitivity(self.addr, sensitivity)
end

function Wiimote:setAspectRatio( ratio )
	libwii.setAspectRatio(self.addr, ratio)
end

function Wiimote:getEvent(  )
	return libwii.getEvent( self.addr )
end

function Wiimote:getId(  )
	return libwii.getId( self.addr )
end

function Wiimote:pressed( key )
	return libwii.pressed( self.addr, key )
end

function Wiimote:justPressed( key )
	return libwii.justPressed( self.addr, key )
end

function Wiimote:released( key )
	return libwii.released( self.addr, key )
end

function Wiimote:held( key )
	return libwii.held( self.addr, key )
end

function Wiimote:getRPY(  )
	return libwii.getRPY( self.addr )
end

function Wiimote:getIRPosition(  )
	return libwii.getIRPosition( self.addr )
end
