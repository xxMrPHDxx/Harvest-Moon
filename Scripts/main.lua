game = Game:new(640, 480, 'Harvest Moon!')
game:set_scale(3, 3)

jack = SpriteSheet:new('Sheets/6791.png')
jack:define('jack_walk_down1', 29, 121, 16, 25);
jack:define('jack_walk_down2', 46, 121, 16, 25);
jack:define('jack_walk_down3', 63, 121, 16, 25);
jack:define('jack_walk_left1', 30, 146, 16, 25);
jack:define('jack_walk_left2', 47, 146, 16, 25);
jack:define('jack_walk_left3', 64, 146, 16, 25);
jack:define('jack_walk_up1', 31, 171, 16, 25);
jack:define('jack_walk_up2', 48, 171, 16, 25);
jack:define('jack_walk_up3', 65, 171, 16, 25);

local create_walk = function(ss, name)
	local obj = Animation:new(jack, 180)
	for i=1,3 do obj:add(name..i) end
	obj:add(name..'2')
	return obj
end

jack_walk_down = create_walk(jack, 'jack_walk_down')
jack_walk_left = create_walk(jack, 'jack_walk_left')
jack_walk_up   = create_walk(jack, 'jack_walk_up')


while game:is_open() do
	while game:poll_event() do
		if game:is_event_closed() then game:close() end
	end
	
	game:clear()

	jack_walk_left:update()	
	game:draw(jack_walk_left:get())
	
	game:display()
end

jack_walk_left:destroy()
jack:destroy()
game:destroy()
