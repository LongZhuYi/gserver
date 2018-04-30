local GClass = GClass
local print = print
local setmetatable = setmetatable

module("Player", package.seeall)

local PlayerModuleName = {
	bag     = "Bag",
}

function getModuleTbName(self, mName)
	local tbName = PlayerModuleName[mName]
	return tbName
end

function new(self, rid)
	local o = {rid=rid}
	setmetatable(o, {__index=IndexFunc})
	return o
end

function IndexFunc(tb, mName)
	local obj = rawget(tb ,mName)
	if not obj then 
		local tbName = PlayerModuleName[mName]
		obj = GClass:LoadClass(tbName, tb.rid)
		rawset(tb ,mName, obj)
	end
	return obj
end