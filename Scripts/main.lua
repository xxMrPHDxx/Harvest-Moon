game = Game:new(640, 480, 'Shit!')
jack = SpriteSheet:new('Sheets/6791.png')
jack:define('jack_idle1', 29, 122, 16, 24);
jack:define('jack_idle2', 46, 122, 16, 24);
jack:define('jack_idle3', 63, 122, 16, 24);

while game:is_open() do
	while game:poll_event() do
		if game:is_event_closed() then game:close() end
	end
	
	game:clear()

	local time = game:get_time()
	
	local idx = math.floor(time/180) % 4 + 1
	if idx == 4 then idx = 2 end
	game:draw(jack:get('jack_idle'..idx))
	
	game:display()
end

game:destroy()
