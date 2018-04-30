local table = table
local redis = LHRedis:getRedis()
local getTbName = getTbName

function login(msg)
	local name = msg.name
	local account = loadAccount(name)
	local rid = account.rid 
	local e = Player:new(rid)
	PlayerManager:setPlayer(rid, e)
	return 1
end

function oper1(msg)
	local rid = msg.rid
	local player = PlayerManager:getPlayer(rid)
	print(player.bag)
end

function tick(msg)
	--{["rid"]=17,["fName"]="oper1"}
end

function loadFromDb(tName, key)
	local tb = redis:query(tName, key) or {}
	return tb
end

function loadAccount(name)
	local account = loadFromDb("Account", name)
	if not account then 
		account = createAccount(name)
	end
	return account
end

function createAccount(name)
	local  rid = redis:Incr("GNormal", "Rid")
	local account = {rid=rid, name=name}
	redis:update("Account", name, account)
	return account
end

local Funcs = {
	login = login,
	oper1 = oper1,
} 

function excute(m)
	local msg = table:unserialize(m.msg)
	local fName = msg.fName
	local rid     = msg.rid
	local func = Funcs[fName]
	assert(func)
	if fName == "login" then
		login(msg)
		return
	end
	local obj  = PlayerManager:getPlayer(rid)
	rpcco:excuteC(obj, func, msg)
end

--[[
	{["rid"]=100,["fName"]="login",["name"]="Long"}
]]