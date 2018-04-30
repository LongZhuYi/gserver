module("Player", package.seeall)

function new(self, rid)
	local o = {rid=rid}
	setmetatable(o, {__index=self})
	return o
end