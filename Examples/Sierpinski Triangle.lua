-- Sierpinski Triangle

setcolor(255,255,255,255)

function sierpinski(x1,y1,x2,y2,x3,y3,depth)
    if depth == 0 then
        renderline(x2,x1,y2,y1)
        renderline(x3,x2,y3,y2)
        renderline(x1,x3,y1,y3)
    else
        local mid_ab_x = (x1 + x2) / 2
        local mid_ab_y = (y1 + y2) / 2
        local mid_bc_x = (x2 + x3) / 2
        local mid_bc_y = (y2 + y3) / 2
        local mid_ca_x = (x3 + x1) / 2
        local mid_ca_y = (y3 + y1) / 2

        sierpinski(x1,y1,mid_ab_x,mid_ab_y,mid_ca_x,mid_ca_y,depth-1)
        sierpinski(x2,y2,mid_ab_x,mid_ab_y,mid_bc_x,mid_bc_y,depth-1)
        sierpinski(x3,y3,mid_ca_x,mid_ca_y,mid_bc_x,mid_bc_y,depth-1)
    end
end

local width = 650
local height = 500
local margin = 50
local half = (width - margin*2) / 2

local x1 = width / 2
local y1 = margin

local x2 = x1 - half
local y2 = height - margin

local x3 = x1 + half
local y3 = height - margin

sierpinski(x1,y1,x2,y2,x3,y3,5)