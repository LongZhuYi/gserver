local HRedis = HRedis

function HRedis:new()
	local o = o or {}
	o.redis = HRedis()
	setmetatable(o, {__index = self})
	return o
end

function HRedis:query(tName, key)
	local cmd = string.format("hget %s %s", tName, key)
	local res = self:excute(cmd)
	return res
end

function HRedis:update(tName, key, val)
	local cmd = string.format("hset %s %s %s", tName, key, tostring(val))
	local res = self:excute(cmd)
	return res
end
