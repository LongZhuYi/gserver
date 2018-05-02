module("Observer", package.seeall)

function new(self)
	local o = {__list={}}
	setmetatable(o, {__index=self})
	return o
end

function add(self, eventId, func)
	self.__list[eventId] = self.__list[eventId] or {}
	table.insert( self.__list[eventId], func )
end

function Observer:del(self, eventId, func)
	--todo
end

function Observer:dispatch(self, eventId, ...)
	local list = self.__list[eventId]
	if not list then 
		return 
	end
	for _, func in pairs(list) do 
		local result, err = pcall(func, ...)
	end
end