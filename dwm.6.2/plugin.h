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

void tile_left(Monitor *m)
{
  unsigned int i, n, h, mw, my, ty, ns;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

  if(n == 1)
  {
		c = nexttiled(m->clients);
		resize(c, m->wx, m->wy, m->ww - 2 * c->bw, m->wh - 2 * c->bw, 0);
		return;
	}

	if (n > m->nmaster)
  {
		mw = m->nmaster ? m->ww * m->mfact : 0;
    ns = m->nmaster > 0 ? 2 : 1;
  }
	else
  {
    mw = m->ww - m->gappx;
    ns = 1;
  }

  for (i = 0, my = ty = m->gappx, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
		if (i < m->nmaster) 
    {
      h = (m->wh - my) / (MIN(n, m->nmaster) - i) - m->gappx;
      //resize(c, m->wx + m->gappx, m->wy + my, mw - 2*c->bw - m->gappx*(5-ns)/2, h - 2*c->bw, 0);
      resize(c, m->wx + m->gappx / 2 + m->ww - mw, m->wy + my, mw - (2 * c->bw + m->gappx/2), h - (2*c->bw), 0);
      //resize(c, m->wx + m->ww - mw, m->wy + my, mw - (2*c->bw), h - (2*c->bw), 0);
      if (my + HEIGHT(c) + m->gappx < m->wh)
        my += HEIGHT(c) + m->gappx;
		} 
    else 
    {
      h = (m->wh - ty) / (n - i) - m->gappx;
      //resize(c, m->wx + mw + m->gappx/ns, m->wy + ty, m->ww - mw - (2*c->bw) - m->gappx*(5-ns)/2, h - 2*c->bw, 0);
      //resize(c, m->wx + m->gappx/ns, m->wy + ty, m->ww - mw - (2*c->bw), h - (2*c->bw), 0);
      resize(c, m->wx, m->wy + ty, m->ww - mw - (2*c->bw) - m->gappx/4, h - (2*c->bw), 0);
      if(ty + HEIGHT(c) + m->gappx < m->wh)
        ty += HEIGHT(c) + m->gappx;
		}
}


// horizontal stack layout
void horizgrid(Monitor *m) {
	Client *c;
	unsigned int n, i;
	int w = 0;
	int ntop, nbottom = 0;

	/* Count windows */
	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);

	if(n == 0)
		return;
	else if(n == 1) { /* Just fill the whole screen */
		c = nexttiled(m->clients);
		resize(c, m->wx, m->wy, m->ww - (2*c->bw), m->wh - (2*c->bw), False);
	} else if(n == 2) { /* Split vertically */
		w = m->ww / 2;
		c = nexttiled(m->clients);
		resize(c, m->wx, m->wy, w - (2*c->bw), m->wh - (2*c->bw), False);
		c = nexttiled(c->next);
		resize(c, m->wx + w, m->wy, w - (2*c->bw), m->wh - (2*c->bw), False);
	} else {
		ntop = n / 2;
		nbottom = n - ntop;
		for(i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
			if(i < ntop)
				resize(c, m->wx + i * m->ww / ntop, m->wy, m->ww / ntop - (2*c->bw), m->wh / 2 - (2*c->bw), False);
			else
				resize(c, m->wx + (i - ntop) * m->ww / nbottom, m->wy + m->wh / 2, m->ww / nbottom - (2*c->bw), m->wh / 2 - (2*c->bw), False);
		}
	}
}
