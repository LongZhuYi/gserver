local Funcs = {
	login = login,
	oper1 = oper1,
}

function excute(funNmae, rid, ...)
	print("------excute----------")
	local func = Funcs[funNmae]
	local obj  = entityM:getEntity(rid)
	assert(func)
	rpcco.excute(obj, func, ...)
end

function loadFromDb(name)
	return {rid=100}
end

function loadAccount(name)
	local account = loadFromDb(name)
	return account
end

function login(name)
	local account = loadAccount(name)
	local rid = account.rid 
	local entity = entity:new(rid)
end

function oper1(obj)

end