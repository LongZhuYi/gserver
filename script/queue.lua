queue = queue or {}

function queue:new()
	local o = {head=0, tail=0, que={}}
	setmetatable(o, {__index=self})
	return o
end

function queue:push(item)
	self.tail = self.tail+1
	self.que[self.tail] = item
end

function queue:pop()
	if self.head == self.tail then 	return nil end
	self.head = self.head+1
	local item = self.que[self.head]
	return item
end

function queue:size()
	return self.tail - self.head
end