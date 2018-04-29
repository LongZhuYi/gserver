--local Observer =Observer

module("ServerManager", package.seeall)

local __ServerList__ = __ServerList__ or {}
--local __observer = Observer:new()

function init()
	
end

function onServerUp(sid, ip, port)
	__ServerList__[sid] = {ip=ip, port=port}
	__observer:dispathch(Event.ServerUp, sid, ip, port)
end

function onServerFail(sid)
	__ServerList__[sid] = nil
	__observer:dispathch(Event.ServerFail, sid)
end

function tick(new, delay)
	for sid, ser in pairs(__ServerList__) do 
		-- todo tick 
	end
end