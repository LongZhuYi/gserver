module "entityManager"

local __EntityList__ = {}
entityM = entityM or {}

function entityM:setEntity(rid, entity)
	__EntityList__[rid] = entity
end

function entityM:getEntity(rid)
	return __EntityList__[rid]
end
