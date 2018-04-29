local HRedis = HRedis
local trim = trim

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

function oper1(obj)

end

local Funcs = {
	login = login,
	oper1 = oper1,
}

function excute(funNmae, rid, ...)
	local funNmae = trim(funNmae)
	local rid     = math.floor(rid)
	local func = Funcs[funNmae]
	print("----------excute---------------", funNmae, rid, func)
	assert(func)
	local obj  = entity:new(rid)
	rpcco:excuteC(obj, func, ...)
end

function loadFromDb(tName, key)
	print("loadFromDb000")
	local redis  = HRedis()
	local tb = redis:query(tName, key)
	if not tb then 
		-- tb = {name="Long", rid=10001}
		-- redis:update(tName, key, tb)
		print("-----nilnilnil------------")
	end
	return tb
end

function loadAccount(name)
	local account = loadFromDb("Account", name)
	return account
end



