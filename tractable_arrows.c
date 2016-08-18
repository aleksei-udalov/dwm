/* This functions proxies some function calls. The goal is make arrows keys 
behavior more transparent. Now with bstack layout active keys up and down 
changes master area size. Keys left and right changes master area client count 
*/

static Arg narg;

void proxy_up(const Arg *arg) {

//	if (strcmp(selmon->ltsymbol, "TTT"))
	if (!(selmon->ltsymbol[0] == 'T'))
  {
  	narg.i = 1;
		incnmaster(&narg);
	}
	else
	{
		narg.f = -0.05;
		setmfact(&narg);
	}
}
void
proxy_down(const Arg *arg)
{
//	if (strcmp(selmon->ltsymbol, "TTT"))
	if (!(selmon->ltsymbol[0] == 'T'))
	{
		narg.i = -1;
		incnmaster(&narg);
	}
	else
	{
		narg.f = 0.05;
		setmfact(&narg);
	}
}
void
proxy_left(const Arg *arg)
{
//	if (!strcmp(selmon->ltsymbol, "TTT"))
	if (selmon->ltsymbol[0] == 'T')
	{
		// if bstack layout selected. master area located at the top
		narg.i = 1;
		incnmaster(&narg); // change master area client count
	}
	else
	{
		// if tile (or another) layout selected. master area located at the left
		narg.f = -0.05;
		setmfact(&narg); // change master area size
	}
}
void
proxy_right(const Arg *arg)
{
//	if (!strcmp(selmon->ltsymbol, "TTT"))
	if (selmon->ltsymbol[0] == 'T')
	{
		narg.i = -1;
		incnmaster(&narg);
	}
	else
	{
		narg.f = 0.05;
		setmfact(&narg);
	}
}
