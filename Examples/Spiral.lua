-- Spiral

function line(x1,y1,x2,y2)
    renderline(x2,x1,y2,y1)
end

local cx = 325
local cy = 250

local turns = 1200
local maxr = 220

for i = 1, turns do
    local t = i / turns
    local angle = i * 0.15
    local r1 = t * maxr
    local r2 = (t + 0.01) * maxr

    local x1 = cx + r1 * math.cos(angle)
    local y1 = cy + r1 * math.sin(angle)

    local x2 = cx + r2 * math.cos(angle + 0.4)
    local y2 = cy + r2 * math.sin(angle + 0.4)

    local red   = math.floor(128 + 127 * math.sin(i * 0.02))
    local green = math.floor(128 + 127 * math.sin(i * 0.03 + 2))
    local blue  = math.floor(128 + 127 * math.sin(i * 0.04 + 4))

    setcolor(red,green,blue,255)

    line(x1,y1,x2,y2)
end