local HRedis = HRedis
local table  = table
local trim = trim

module("LHRedis", package.seeall)

function LHRedis:new()
	local o = o or {}
	o.redis = HRedis()
	setmetatable(o, {__index = self})
	return o
end

function LHRedis:query(tName, key)
	local cmd = string.format("hget %s %s", tName, key)
	local res = self.redis:excute(cmd)
	res = trim(res)
	local tb  = table:unserialize(res)
	return tb
end

function LHRedis:update(tName, key, val)
	local seri = table:serialize(val)
	local cmd = string.format("hset %s %s %s", tName, tostring(key), seri)
	local res = self.redis:excute(cmd)
	return res
end

function LHRedis:Incr(tName)
	local seri = table.serialize(incr)
	local cmd = string.format("incr %s", tName);
	local res = self.redis:excute(cmd)
	res = table:unserialize(res)
	return res
end