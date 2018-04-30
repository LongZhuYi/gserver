local HRedis = HRedis
local table  = table
local trim = trim

local GRedis = nil

module("LHRedis", package.seeall)

function getRedis(self)
	if not GRedis then
		GRedis = LHRedis:new();
	end
	return GRedis
end

function new(self)
	local o = o or {}
	o.redis = HRedis()
	setmetatable(o, {__index = self})
	return o
end

function query(self, tName, key)
	local cmd = string.format("hget %s %s", tName, key)
	local res = self.redis:excute(cmd)
	res = trim(res)
	local tb  = table:unserialize(res)
	return tb
end

function update(self, tName, key, val)
	local seri = table:serialize(val)
	local cmd = string.format("hset %s %s %s", tName, tostring(key), seri)
	local res = self.redis:excute(cmd)
	return res
end

function Incr(self, tName)
	local seri = table.serialize(incr)
	local cmd = string.format("incr %s", tName);
	local res = self.redis:excute(cmd)
	res = table:unserialize(res)
	return res
end