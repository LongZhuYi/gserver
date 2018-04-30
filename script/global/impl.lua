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
	--print("lua tick", id)
end

function excute(funNmae, rid, ...)
	local funNmae = trim(funNmae)
	local rid     = math.floor(rid)
	local func = Funcs[funNmae]
	assert(func)
	local obj  = entity:new(rid)
	rpcco:excuteC(obj, func, ...)
end

function login(name)
	print("login bbb")
	local name = "Long"
	local account = loadAccount(name)
	local rid = account.rid 
	local e = entity:new(rid)
	entityM:setEntity(rid, e)
	print("login", e.rid)
	return 1
end

function loadFromDb(tName, key)
	local tb = redis:query(tName, key)
	if not tb then 
		tb = createAccount(key)
	end
	return tb
end

function loadAccount(name)
	local account = loadFromDb("Account", name)
	return account
end

function createAccount(name)
	local  rid = redis:Incr("GNormal", "Rid", 1)
	local account = {rid=rid, name=name}
	return account
end

