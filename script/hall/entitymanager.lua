--module("entityManager", package.seeall)

local __EntityList__ = {}
entityM = entityM or {}

function entityM:setEntity(rid, entity)
	__EntityList__[rid] = entity
end

function entityM:getEntity(rid)
	return __EntityList__[rid]
end

function entityM:update(delay)
	for rid, e in pairs(__EntityList__) do 
		e:update(delay)
	end
end