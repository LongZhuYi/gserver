
heap = heap or {}

function heap:new()
	local o = {data={}}
	setmetatable(o, {__index=self})
	return o
end

function heap:push(item)
	assert(item and item.key)
	table.insert(self.data, item)
	self:upper(#self.data)
end

function heap:pop()
	if #self.data == 0 then return end
	self.data[1] = self.data[#self.data]
	self.data[#self.data] = nil 
	self:lower(1)
end

function upper(pos)
	while pos > 1 then
		local p = math.floor(pos/2)
		if self.data[pos].key < self.data[p].key then 
			self.data[pos], self.data[p] = self.data[p], self.data[pos]
			pos = p
		else
			break 
		end
	end
end

function lower(pos)
	while pos < self:size() do
		local l = pos*2 
		local r = pos*2+1
		if self.data[l] and self.data[pos].key > self.data[l].key then
			self.data[pos], self.data[l] = self.data[l], self.data[pos]
			pos = l
		else
			break
		end
		if self.data[r] and self.data[pos].key > self.data[r].key then 
			self.data[pos], self.data[r] = self.data[r], self.data[pos]
			pos = r
		else
			break
		end
	end
end

function size()
	return #self.data
end

function heap:top()
	return self.data[1]
end

function heap:parent(pos) return math.floor(pos/2) end
function heap:left(pos) return pos*2 end
function heap:right(pos) return 2*pos+1 end