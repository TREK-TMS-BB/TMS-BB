# G and H used as temporaries

clear F;
clear G;
clear H;

incr G;
incr G;


while G not 0 do;
	incr F;
	incr F;
	while F not 0 do;
		incr H;
		while H not 0 do;
			incr J;
			decr H;
		end;
		dec F;
	end;
	decr G;
end;