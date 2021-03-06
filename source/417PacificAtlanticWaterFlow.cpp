
class Solution {
public:
	vector<pair<int, int>> res;
	vector<vector<int>> visited;
	void dfs(vector<vector<int>>& matrix, int x, int y, int pre, int preval) {
		if (x < 0 || x >= matrix.size() || y<0 || y>=matrix[0].size() || matrix[x][y] < pre || (visited[x][y] & preval) == preval)
			//(visited[x][y] & preval == preval）找了好半天的错误，尼玛，&的优先级是最低的。
            //this judgement is to avoid cyclic search
            //matric[x][y]<pre is to find the posiztion higher than it
            //
			return;
		visited[x][y] |= preval;  //not += instead it's |=
		if (visited[x][y] == 3)  //the posiztion that two ocean can reach.
			res.push_back({ x,y });
		dfs(matrix, x + 1, y, matrix[x][y], visited[x][y]);
		dfs(matrix, x, y - 1, matrix[x][y], visited[x][y]);
		dfs(matrix, x, y + 1, matrix[x][y], visited[x][y]);
		dfs(matrix, x - 1, y, matrix[x][y], visited[x][y]);
	}

	vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
		if (matrix.empty())
			return res;
		int m = matrix.size();
		int n = matrix[0].size();
		visited.resize(m, vector<int>(n, 0));
		for (int i = 0; i < m; i++) {
			dfs(matrix, i, 0, INT_MIN, 1);//1 mean 0b01,it's the palce pacific can reach
			dfs(matrix, i, n - 1, INT_MIN, 2);//2 mean 0b10,it's a flag to indicate Atlantic can reach
		}
		for (int j = 0; j < n; j++) {
			dfs(matrix, 0, j, INT_MIN, 1);
			dfs(matrix, m - 1, j, INT_MIN, 2);
		}
		return res;
	}
};
