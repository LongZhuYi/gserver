require "hall/entity"
require "hall/entitymanager"
require "base/rpcco"

function login(name)
	print("login bbb")
	local account = loadAccount(name)
	local rid = account.rid 
	local e = entity:new(rid)
	print("login", e.rid)
	return 1
end

function oper1(obj)

end

function trim(s) 
	return (string.gsub(s, "^%s*(.-)%s*$", "%1"))
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

function loadFromDb(name)
	return {rid=100}
end

function loadAccount(name)
	local account = loadFromDb(name)
	return account
end



