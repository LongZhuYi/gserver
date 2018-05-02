--module("impl", package.seeall)
local trim = trim
local redis  = LHRedis()

local Funcs = {
	[Event.ServerUp] = ServerManager.onServerUp,
	[Event.ServerFail] = ServerManager.onServerFail,
}

function tick(msg)
	local id = msg.id
	Timer:tick(id)
end

function excute(m)
	local msg = table:unserialize(m.msg)
	local fName = msg.fName
	local rid     = msg.rid
	local rid     = math.floor(rid)
	local func = Funcs[fName]
	assert(func)
	rpcco:excuteC(nil, func, msg)
end
