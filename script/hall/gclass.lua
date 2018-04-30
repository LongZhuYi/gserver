local getTbName = getTbName
local string = string
local assert = assert
local __Class__ = __Class__ or {}

module("GClass", package.seeall)

function Register(self, name, class)
	__Class__[name] = class
end

function LoadClass(self, tbName, rid)
	local data = loadFromDb(tbName, rid)
	local class = __Class__[tbName]
	assert(class, string.format("can't find class name=%s", tbName))
	local obj = class:new()
	obj:init(data)
	return obj
end