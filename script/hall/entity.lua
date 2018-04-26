module "entity"

entity = entity or {}

function entity:new(rid)
	local o = {rid=rid}
	setmetatable(o, {__index=self})
	return o
end