--module("Observer", package.seeall)

Observer =  Observer or {}

function Observer:new()
	local o = {__list={}}
	setmetatable(o, {__index=self})
	return o
end

function Observer:add(eventId, func)
	self.__list[eventId] = self.__list[eventId] or {}
	table.insert( self.__list[eventId], func )
end

function Observer:del(eventId, func)
	--todo
end

function Observer:dispatch(eventId, ...)
	local list = self.__list[eventId]
	if not list then 
		return 
	end
	for _, func in pairs(list) do 
		local result, err = pcall(func, ...)
	end
end