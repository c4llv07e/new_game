function HSVToRGB( hue, saturation, value )
	if saturation == 0 then
		return value, value, value;
	end;

	local hue_sector = math.floor( hue / 60 );
	local hue_sector_offset = ( hue / 60 ) - hue_sector;

	local p = value * ( 1 - saturation );
	local q = value * ( 1 - saturation * hue_sector_offset );
	local t = value * ( 1 - saturation * ( 1 - hue_sector_offset ) );

	if hue_sector == 0 then
		return value, t, p;
	elseif hue_sector == 1 then
		return q, value, p;
	elseif hue_sector == 2 then
		return p, value, t;
	elseif hue_sector == 3 then
		return p, q, value;
	elseif hue_sector == 4 then
		return t, p, value;
	elseif hue_sector == 5 then
		return value, p, q;
	end;
end;

function circuit(x,y,r,t)
	for i = 0, 360/t-1 do
    draw_line(math.sin((i*t+t)/57.295)*r+x, math.cos((i*t+t)/57.295)*r+y, math.sin(i*t/57.295)*r+x, math.cos(i*t/57.295)*r+y)
	end
	for i = 0, (r*2)/t-1 do
    draw_line(math.sin(i*t/57.295)*r*(-1)+x, math.cos(i*t/57.295)*r+y, math.sin(i*t/57.295)*r+x, math.cos(i*t/57.295)*r+y)
	end
	for i = 0, (r*2)/t do
    draw_line(math.sin(i*t/57.295)*r+x, math.cos(i*t/57.295)*r*-1+y, math.sin(i*t/57.295)*r+x, math.cos(i*t/57.295)*r+y)
	end
end


cl = 6

function mouse_click()
	print("a")
	cl = cl+1
end


x, y = get_mouse_pos()
--[[
e = 1
for i = 0, 360*e-1 do
    a,b,c = HSVToRGB(i/e, 1, 1)
    draw_color_line(x, y, (math.sin(i/e/56)*100)+(i/1.8/e)+x-100, math.cos(i/e/56)*100+y, a*255, b*255, c*255, 255)
end]]


cord = {30,20,0,50,100,150,50,200,0,150,100,50,70,20}

for i=1, cl do
  draw_color_line(cord[i*2-1],cord[i*2],cord[i*2+1],cord[i*2+2], 255, 0, 0, 255)
end

draw_color_line(50,20,50,200, 255, 0, 0, 255)

if time % 50 > 25 then
   game_ent_disable_render(ref)
else
   game_ent_enable_render(ref)
end

time = time + 1
