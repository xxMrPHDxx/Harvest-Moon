game = Game:new(640, 480, 'Shit!')

while game:is_open() do
	while game:poll_event() do
		if game:is_event_closed() then game:close() end
	end

	game:display()
end

game:destroy()
