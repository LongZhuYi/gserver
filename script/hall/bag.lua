local table = table
local pairs = pairs

module("Bag", package.seeall)

function new(self)
	local o = {}
	setmetatable(o, {__index=self})
	return o
end

function init(self, data)
	self.data = {}
	for k,v in pairs(data) do 
		self.data[k] = table.unserialize(v)
	end
end

GClass:Register("Bag", Bag)