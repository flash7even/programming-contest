struct node{
    int count;
    node * left;
    node * right;
	node(int count, node *left, node *right):
		count(count), left(left), right(right) {}

    node * ut(int s, int e, int u);
};

node * root[Size];
node * null = new node(0, NULL, NULL);

node * node::ut(int s,int e,int u){
    if(e < u || s > u) return this;
    if(s == e){
        return new node(this->count+1, null, null);
    }
    int M = (s+e)/2;

    node * ln = this->left->ut(s,M,u);
    node * rn = this->right->ut(M+1,e,u);

    return new node(this->count+1, ln, rn);
}

int qt(node * a, node * b, node * c, node * d, int s,int e,int k){
    if(s == e) return s;

    int M = (s+e)/2;

    int leftCnt = a->left->count + b->left->count - c->left->count - d->left->count;

    if(leftCnt >= k){
        return qt(a->left, b->left, c->left, d->left, s, M, k);
    }
    return qt(a->right, b->right, c->right, d->right, M+1, e, k - leftCnt);
}
