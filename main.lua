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


x, y = get_mouse_pos()

e = 0.1
for i = 0, 360*e-1, 1 do
    a,b,c = HSVToRGB(i/e, 1, 1)
    draw_color_line(x, y, (math.sin(i/e/56)*100)+(i/1.8/e)+x-100, math.cos(i/e/56)*100+y, a*255, b*255, c*255, 255)
end

e = 32
for i = 0, 360*e-1 do
    a,b,c = HSVToRGB(i/e, 1, 1)
    draw_color_line(300, 100, (math.sin(i/e/56)*100)+(i/1.8/e)+200, math.cos(i/e/56)*100+100, a*255, b*255, c*255, 255)
end
