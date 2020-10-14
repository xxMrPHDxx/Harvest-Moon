game = Game:new(640, 480, 'Shit!')
jack = SpriteSheet:new('Sheets/6791.png')
jack:define('test', 0, 0, 16, 16);

while game:is_open() do
	while game:poll_event() do
		if game:is_event_closed() then game:close() end
	end
	
	game:clear()
	game:draw(jack:get('test'))
	game:display()
end

game:destroy()
