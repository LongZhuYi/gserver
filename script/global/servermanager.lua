local Observer =Observer

module("ServerManager", package.seeall)

local __ServerList__ = __ServerList__ or {}
local __observer = Observer:new()

function init(self)
	__observer:add(Event.ServerUp, self.sendMsgToEach)
end

function onServerUp(self, sid, ip, port)
	__ServerList__[sid] = {ip=ip, port=port}
	local msg = {ip=ip, port=port, type=1}
	__observer:dispathch(Event.ServerUp, sid, msg)
end

function onServerFail(self, sid)
	__ServerList__[sid] = nil
	__observer:dispathch(Event.ServerFail, sid)
end

function tick(self, new, delay)
	for sid, ser in pairs(__ServerList__) do 
		-- todo tick 
	end
end

function sendMsgToEach(self, sid, msg)
	for ssid, v in pairs(__ServerList__) do
		-- sendMsg(sid, msg)
	end
end