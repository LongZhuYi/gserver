local sendMsgToSid = sendMsgToSid

function sendMsg(msg)
	sendMsgToSid(msg.sid, msg.ms)
end

local Funcs = {
	sendMsgToSid = sendMsgToSid,
}

function excute(m)
	local msg = table:unserialize(m.msg)
	local fName = msg.fName
	local sid   = msg.sid
	local func = Funcs[fName]
	assert(func)
	rpcco:excuteC(nil, func, msg)
end

function tick()
	--
end