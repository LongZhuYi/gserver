local HRedis = HRedis
local table  = table

function HRedis:new()
	local o = o or {}
	o.redis = HRedis()
	setmetatable(o, {__index = self})
	return o
end

function HRedis:query(tName, key)
	local cmd = string.format("hget %s %s", tName, key)
	local res = self:excute(cmd)
	res = trim(res)
	print("HRedis:query res=", res)
	local tb  = table:unserialize(res)
	return tb
end

function HRedis:update(tName, key, val)
	local seri = table:serialize(val)
	local cmd = string.format("hset %s %s %s", tName, key, seri)
	local res = self:excute(cmd)
	return res
end
