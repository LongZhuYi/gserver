--module("impl", package.seeall)

local Funcs = {
	[Event.ServerUp] = ServerManager.onServerUp,
	[Event.ServerFail] = ServerManager.onServerFail,
}

function excute(msg)
	local msg = table.unserialize(msg)
	local sid = msg.sid
	local ip  = msg.ip
	local port = msg.port 
	local eventId = msg.eventId 
	Funcs[eventId](sid, ip, port)
end

function tick(msg)
	print("tick", msg)
end