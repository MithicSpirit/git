struct gitdiff_data {
	struct strbuf *root;
	int linenr;
	int p_value;
};

	git_config(git_xmerge_config, NULL);
	/*
	 * Please update $__git_whitespacelist in git-completion.bash
	 * when you add new options.
	 */
static char *find_name_gnu(struct strbuf *root,
	 * https://lore.kernel.org/git/7vll0wvb2a.fsf@assigned-by-dhcp.cox.net/
	if (root->len)
		strbuf_insert(&name, 0, root->buf, root->len);
static char *find_name_common(struct strbuf *root,
	if (root->len) {
		char *ret = xstrfmt("%s%.*s", root->buf, len, start);
static char *find_name(struct strbuf *root,
		char *name = find_name_gnu(root, line, p_value);
	return find_name_common(root, line, def, p_value, NULL, terminate);
static char *find_name_traditional(struct strbuf *root,
		char *name = find_name_gnu(root, line, p_value);
		return find_name_common(root, line, def, p_value, NULL, TERM_TAB);
	return find_name_common(root, line, def, p_value, line + len, 0);
	name = find_name_traditional(&state->root, nameline, NULL, 0);
		name = find_name_traditional(&state->root, second, NULL, state->p_value);
		name = find_name_traditional(&state->root, first, NULL, state->p_value);
		first_name = find_name_traditional(&state->root, first, NULL, state->p_value);
		name = find_name_traditional(&state->root, second, first_name, state->p_value);
static int gitdiff_hdrend(struct gitdiff_data *state,
static int gitdiff_verify_name(struct gitdiff_data *state,
		*name = find_name(state->root, line, NULL, state->p_value, TERM_TAB);
		another = find_name(state->root, line, NULL, state->p_value, TERM_TAB);
static int gitdiff_oldname(struct gitdiff_data *state,
static int gitdiff_newname(struct gitdiff_data *state,
static int gitdiff_oldmode(struct gitdiff_data *state,
static int gitdiff_newmode(struct gitdiff_data *state,
static int gitdiff_delete(struct gitdiff_data *state,
static int gitdiff_newfile(struct gitdiff_data *state,
static int gitdiff_copysrc(struct gitdiff_data *state,
	patch->old_name = find_name(state->root, line, NULL, state->p_value ? state->p_value - 1 : 0, 0);
static int gitdiff_copydst(struct gitdiff_data *state,
	patch->new_name = find_name(state->root, line, NULL, state->p_value ? state->p_value - 1 : 0, 0);
static int gitdiff_renamesrc(struct gitdiff_data *state,
	patch->old_name = find_name(state->root, line, NULL, state->p_value ? state->p_value - 1 : 0, 0);
static int gitdiff_renamedst(struct gitdiff_data *state,
	patch->new_name = find_name(state->root, line, NULL, state->p_value ? state->p_value - 1 : 0, 0);
static int gitdiff_similarity(struct gitdiff_data *state,
static int gitdiff_dissimilarity(struct gitdiff_data *state,
static int gitdiff_index(struct gitdiff_data *state,
	const unsigned hexsz = the_hash_algo->hexsz;
	if (!ptr || ptr[1] != '.' || hexsz < ptr - line)
	memcpy(patch->old_oid_prefix, line, len);
	patch->old_oid_prefix[len] = 0;
	if (hexsz < len)
	memcpy(patch->new_oid_prefix, line, len);
	patch->new_oid_prefix[len] = 0;
static int gitdiff_unrecognized(struct gitdiff_data *state,
static const char *skip_tree_prefix(int p_value,
	if (!p_value)
	nslash = p_value;
static char *git_header_name(int p_value,
		cp = skip_tree_prefix(p_value, first.buf, first.len);
			cp = skip_tree_prefix(p_value, sp.buf, sp.len);
		cp = skip_tree_prefix(p_value, second, line + llen - second);
	name = skip_tree_prefix(p_value, line, llen);
			np = skip_tree_prefix(p_value, sp.buf, sp.len);
			second = skip_tree_prefix(p_value, name + len + 1,
static int check_header_line(int linenr, struct patch *patch)
			     patch->extension_linenr, linenr);
		patch->extension_linenr = linenr;
int parse_git_diff_header(struct strbuf *root,
			  int *linenr,
			  int p_value,
			  const char *line,
			  int len,
			  unsigned int size,
			  struct patch *patch)
	struct gitdiff_data parse_hdr_state;
	patch->def_name = git_header_name(p_value, line, len);
	if (patch->def_name && root->len) {
		char *s = xstrfmt("%s%s", root->buf, patch->def_name);
	(*linenr)++;
	parse_hdr_state.root = root;
	parse_hdr_state.linenr = *linenr;
	parse_hdr_state.p_value = p_value;

	for (offset = len ; size > 0 ; offset += len, size -= len, line += len, (*linenr)++) {
			int (*fn)(struct gitdiff_data *, const char *, struct patch *);
			res = p->fn(&parse_hdr_state, line + oplen, patch);
			if (check_header_line(*linenr, patch))
				goto done;
done:
	if (!patch->old_name && !patch->new_name) {
		if (!patch->def_name) {
			error(Q_("git diff header lacks filename information when removing "
				 "%d leading pathname component (line %d)",
				 "git diff header lacks filename information when removing "
				 "%d leading pathname components (line %d)",
				 parse_hdr_state.p_value),
			      parse_hdr_state.p_value, *linenr);
			return -128;
		}
		patch->old_name = xstrdup(patch->def_name);
		patch->new_name = xstrdup(patch->def_name);
	}
	if ((!patch->new_name && !patch->is_delete) ||
	    (!patch->old_name && !patch->is_new)) {
		error(_("git diff header lacks filename information "
			"(line %d)"), *linenr);
		return -128;
	}
	patch->is_toplevel_relative = 1;
			int git_hdr_len = parse_git_diff_header(&state->root, &state->linenr,
								state->p_value, line, len,
								size, patch);
	if (!patch->recount && !deleted && !added)
	else if (patch->new_name)
		patch->ws_rule = whitespace_rule(state->repo->index,
						 patch->new_name);
		patch->ws_rule = whitespace_rule(state->repo->index,
						 patch->old_name);
		SWAP(p->old_oid_prefix, p->new_oid_prefix);
	/*
	 * When running with --allow-overlap, it is possible that a hunk is
	 * seen that pretends to start at the beginning (but no longer does),
	 * and that *still* needs to match the end. So trust `match_end` more
	 * than `match_beginning`.
	 */
	if (state->allow_overlap && match_beginning && match_end &&
	    img->nr - preimage->nr != 0)
		match_beginning = 0;

	const unsigned hexsz = the_hash_algo->hexsz;
	 * full hex textual object ID for old and new, at least for now.
	if (strlen(patch->old_oid_prefix) != hexsz ||
	    strlen(patch->new_oid_prefix) != hexsz ||
	    get_oid_hex(patch->old_oid_prefix, &oid) ||
	    get_oid_hex(patch->new_oid_prefix, &oid))
		if (strcmp(oid_to_hex(&oid), patch->old_oid_prefix))
	get_oid_hex(patch->new_oid_prefix, &oid);
	if (has_object_file(&oid)) {
				     patch->new_oid_prefix, name);
		if (strcmp(oid_to_hex(&oid), patch->new_oid_prefix))
				name, patch->new_oid_prefix, oid_to_hex(&oid));
	if (checkout_entry(ce, &costate, NULL, NULL) ||
	    lstat(ce->name, st))
static int three_way_merge(struct apply_state *state,
			   struct image *image,
			  &their_file, "theirs",
			  state->repo->index,
			  NULL);
	else if (get_oid(patch->old_oid_prefix, &pre_oid) ||
	status = three_way_merge(state, image, patch->new_name,
		return repo_read_index(state->repo);
	    preimage[sizeof(heading) + the_hash_algo->hexsz - 1] == '\n' &&
	    starts_with(preimage + sizeof(heading) - 1, p->old_oid_prefix))
	return get_oid_hex(p->old_oid_prefix, oid);
		} else if (!get_oid_blob(patch->old_oid_prefix, &oid)) {
	/* p->old_name through old_name is the common prefix, and old_name and
	 * new_name through the end of names are renames
			fill_stat_cache_info(state->repo->index, ce, &st);
		repo_rerere(state->repo, 0);
	int flush_attributes = 0;

			if ((patch->new_name &&
			     ends_with_path_components(patch->new_name,
						       GITATTRIBUTES_FILE)) ||
			    (patch->old_name &&
			     ends_with_path_components(patch->old_name,
						       GITATTRIBUTES_FILE)))
				flush_attributes = 1;
			repo_hold_locked_index(state->repo, &state->lock_file,
					       LOCK_DIE_ON_ERROR);
	if (flush_attributes)
		reset_parsed_attributes();

	BUG_ON_OPT_NEG(unset);


	BUG_ON_OPT_NEG(unset);


	BUG_ON_OPT_NEG(unset);


	BUG_ON_OPT_ARG(arg);


	BUG_ON_OPT_NEG(unset);

		return -1;

	BUG_ON_OPT_NEG(unset);

			PARSE_OPT_NONEG, apply_option_parse_exclude },
			PARSE_OPT_NONEG, apply_option_parse_include },