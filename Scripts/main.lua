game = Game:new(640, 480, 'Shit!')

jack = SpriteSheet:new('Sheets/6791.png')
jack:define('jack_idle1', 29, 122, 16, 24);
jack:define('jack_idle2', 46, 122, 16, 24);
jack:define('jack_idle3', 63, 122, 16, 24);

jack_walk = Animation:new(jack, 180)
for i=1,3 do jack_walk:add('jack_idle'..i) end
jack_walk:add('jack_idle2')

while game:is_open() do
	while game:poll_event() do
		if game:is_event_closed() then game:close() end
	end
	
	game:clear()

	-- local time = game:get_time()
	
	jack_walk:update()
	game:draw(jack_walk:get())
	
	game:display()
end

jack_walk:destroy()
jack:destroy()
game:destroy()
