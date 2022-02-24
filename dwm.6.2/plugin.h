static void view_adjacent(const Arg *arg);
static void attachaside(Client *c);

static const char *tagsd[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30" };

// switch tag m_i m_u
void view_adjacent(const Arg *arg)
{
	int i, curtags;
	int seltag = 0;
	Arg a;

	curtags = selmon->tagset[selmon->seltags];
	for(i = 0; i < LENGTH(tagsd); i++)
		if(curtags & (1 << i)){
			seltag = i;
			break;
		}

	seltag = (seltag + arg->i) % (int)LENGTH(tagsd);
	if(seltag < 0)
		seltag += LENGTH(tagsd);

	a.i = (1 << seltag);
	view(&a);
}

// add new win to stak
void attachaside(Client *c) 
{
  Client *at = nexttiled(c->mon->clients);;
  if(c->mon->sel == NULL || c->mon->sel->isfloating || !at) 
  {
    attach(c);
    return;
  }
  c->next = at->next;
  at->next = c;
}

// new layout as center
void tcl(Monitor * m)
{
	int x, y, h, w, mw, sw, bdw;
	unsigned int i, n;
	Client * c;

	for (n = 0, c = nexttiled(m->clients); c;
	        c = nexttiled(c->next), n++);

	if (n == 0)
		return;

	c = nexttiled(m->clients);

	mw = m->mfact * m->ww;
	sw = (m->ww - mw) / 2;
	bdw = (2 * c->bw);
	resize(c,
	       n < 3 ? m->wx : m->wx + sw,
	       m->wy,
	       n == 1 ? m->ww - bdw : mw - bdw,
	       m->wh - bdw,
	       False);

	if (--n == 0)
		return;

	w = (m->ww - mw) / ((n > 1) + 1);
	c = nexttiled(c->next);

	if (n > 1)
	{
		x = m->wx + ((n > 1) ? mw + sw : mw);
		y = m->wy;
		h = m->wh / (n / 2);

		if (h < bh)
			h = m->wh;

		for (i = 0; c && i < n / 2; c = nexttiled(c->next), i++)
		{
			resize(c,
			       x,
			       y,
			       w - bdw,
			       (i + 1 == n / 2) ? m->wy + m->wh - y - bdw : h - bdw,
			       False);

			if (h != m->wh)
				y = c->y + HEIGHT(c);
		}
	}

	x = (n + 1 / 2) == 1 ? mw : m->wx;
	y = m->wy;
	h = m->wh / ((n + 1) / 2);

	if (h < bh)
		h = m->wh;

	for (i = 0; c; c = nexttiled(c->next), i++)
	{
		resize(c,
		       x,
		       y,
		       (i + 1 == (n + 1) / 2) ? w - bdw : w - bdw,
		       (i + 1 == (n + 1) / 2) ? m->wy + m->wh - y - bdw : h - bdw,
		       False);

		if (h != m->wh)
			y = c->y + HEIGHT(c);
	}
}
