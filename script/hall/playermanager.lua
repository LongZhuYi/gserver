module("PlayerManager", package.seeall)

local __PlayerList__ = __PlayerList__ or {}

function setPlayer(self, rid, player)
	__PlayerList__[rid] = player
end

function getPlayer(self, rid)
	return __PlayerList__[rid]
end

function tick(delay)
	-- for rid, e in pairs(__PlayerList__) do 
	-- 	e:tick(delay)
	-- end
end