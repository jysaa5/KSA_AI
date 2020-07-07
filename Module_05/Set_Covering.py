# p.197 집합 커버링 문제

# 방송하고자 하는 주의 목록
states_need = set(["mt", "wa", "or", "id", "nv", "ut", "ca", "az"])

# 방송국의 목록
stations = {}
stations["kone"] = set(["id", "nv", "ut"])
stations["ktwo"] = set(["wa", "id", "mt"])
stations["kthree"] = set(["or", "nv", "ca"])
stations["kfour"] = set(["nv", "ut"])
stations["kfive"] = set(["ca", "az"])


# 내가 방문할 방송국의 목록을 저장할 집합
final_stations = set()

# best_station: 모든 방송국을 하나씩 보면서 아직 방송이 되지 않는 주 중에서 가장 많은 주를 커버하고 있는 방송국
best_station = None

# states_covered: 아직 방송되지 않은 주 중에서 해당 방송국이 커버하는 주의 집합
states_covered = set()

