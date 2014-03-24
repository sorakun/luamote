
require ("wii")

print("init")

wii.init(1)

print("finding")

wii.find(1, 3)

print("connecting")

print(wii.connect(1))

wm1 = Wiimote:new(wii.getMote(0))

wm1:setLed(wii.WIIMOTE_LED_4)

wm1:setIR(wii.ON)

local i = 0

while true do
	local a = wii.poll(1)
	if a > 0 then
		if wm1:getEvent() == wii.WII_EVENT then
			if wm1:justPressed(wii.WIIMOTE_BUTTON_ONE) then
				wm1:setLed(wii.WIIMOTE_LED_1)
			elseif wm1:justPressed(wii.WIIMOTE_BUTTON_TWO) then
				wm1:setLed(wii.WIIMOTE_LED_2)
			end
		end
	end
end
