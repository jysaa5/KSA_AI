#!/usr/bin/env python
# coding: utf-8

# In[4]:


# 데이터 가져오기
# 모듈 설정
# 파이썬 ≥ 3.5

import sys
assert sys.version_info >= (3,5)


# In[5]:


# 데이터 가져오기
# 모듈 설정
# 공통 모듈 임포트

import sklearn
assert sklearn.__version__>= "0.20"


# In[6]:


# 데이터 가져오기
# 모듈 설정
# 공통 모듈 임포트

import numpy as np
import os


# In[7]:


# 데이터 가져오기
# 모듈 설정

#깔끔한 그래프 출력을 위해
get_ipython().run_line_magic('matplotlib', 'inline')
import matplotlib as mpl
import matplotlib.pyplot as plt

mpl.rc('axes', labelsize = 14)
mpl.rc('xtick', labelsize = 12)
mpl.rc('ytick', labelsize = 12)


# In[8]:


# 데이터 가져오기
# 모듈 설정

#그림을 저장할 위치
PROJECT_ROOT_DIR = "."
CHAPTER_ID = "end_to_end_project"
IMAGES_PATH = os.path.join(PROJECT_ROOT_DIR, "images", CHAPTER_ID)
os.makedirs(IMAGES_PATH, exist_ok=True)

def save_fig(fig_id, tight_layout=True, fig_extension = "png", resolution=300):
    path = os.path.join(IMAGES_PATH, fig_id + "."+fig_extension)
    print("그림 저장:", fig_id)
    if tight_layout:
        plt.tight_layout()
    plt.savefig(path, format=fig_extension, dpi=resolution)
    
#불필요한 경고를 무시합니다. 
import warnings
warnings.filterwarnings(action="ignore", message = "^internal gelsd")


# In[9]:


# 데이터 가져오기
# 데이터 다운로드

import os
import tarfile
import urllib

DOWNLOAD_ROOT = "https://raw.githubusercontent.com/rickiepark/handson-ml2/master/"
HOUSING_PATH = os.path.join("datasets", "housing")
HOUSING_URL = DOWNLOAD_ROOT + "datasets/housing/housing.tgz"

def fetch_housing_data(housing_url=HOUSING_URL, housing_path=HOUSING_PATH):
    if not os.path.isdir(housing_path):
        os.makedirs(housing_path)
    tgz_path = os.path.join(housing_path, "housing.tgz")
    urllib.request.urlretrieve(housing_url, tgz_path)
    housing_tgz = tarfile.open(tgz_path)
    housing_tgz.extractall(path=housing_path)
    housing_tgz.close()


# In[10]:


# 데이터 가져오기
# 데이터 다운로드

fetch_housing_data()


# In[11]:


# 데이터 구조 훑어보기
# 데이터 읽어오기

import pandas as pd

def load_housing_data(housing_path=HOUSING_PATH):
    csv_path = os.path.join(housing_path, "housing.csv")
    return pd.read_csv(csv_path)


# In[12]:


# 데이터 구조 훑어보기
# 데이터 읽어오기

housing = load_housing_data()
housing.head()


# In[13]:


# 데이터 구조 훑어보기
# 데이터 간략 설명

housing.info()
housing["ocean_proximity"].value_counts()


# In[14]:


# 데이터 구조 훑어보기
# 숫자형 특성의 요약 정보

housing.describe()


# In[15]:


# 데이터 구조 훑어보기
# 모든 숫자형 특성의 히스토그램

get_ipython().run_line_magic('matplotlib', 'inline')
import matplotlib.pyplot as plt
housing.hist(bins=50, figsize=(20,15))
save_fig("attribute_histogram_plots")
plt.show()


# In[16]:


# 데이터 떼어놓기
# 뇌가 과대적합이 되기 힘들기 때문에 데이터를 떼어 놓아야 함

from sklearn.model_selection import train_test_split
train_set, test_set = train_test_split(housing, test_size=0.2, random_state=42)
test_set.head()


# In[17]:


# 데이터 떼어놓기
# 도메인 전문가가 경험상 median_income이 중간 주택 가격을 예측하는데 중요하다고 할 때 무작위가 아닌 
# 아래의 비율을 유지하기 위해 계층적 샘플링을 수행

housing["median_income"].hist()


# In[18]:


# 데이터 떼어놓기
# Median_income 카테고리 만들기

housing["income_cat"] = pd.cut(housing["median_income"], bins=[0., 1.5, 3.0, 4.5, 6., np.inf], labels=[1,2,3,4,5])
housing["income_cat"].value_counts()


# In[19]:


# 데이터 떼어놓기
# Median_income 카테고리 만들기

housing["income_cat"].hist()


# In[20]:


# 데이터 떼어놓기
# Median_income 카테고리 기반으로 계층 샘플링 하기

from sklearn.model_selection import StratifiedShuffleSplit
split = StratifiedShuffleSplit(n_splits=1, test_size=0.2, random_state=42)

for train_index, test_index in split.split(housing, housing["income_cat"]):
    strat_train_set = housing.loc[train_index]
    strat_test_set = housing.loc[test_index]

print(strat_test_set["income_cat"].value_counts()/len(strat_test_set))
print(housing["income_cat"].value_counts()/len(housing))


# In[21]:


# 데이터 떼어놓기
# Income_cat 컬럼 지우기

for set_ in(strat_train_set, strat_test_set):
    set_.drop("income_cat", axis=1, inplace=True)


# In[22]:


# 데이터 이해하기
# 지리적 데이터 시각화

housing = strat_train_set.copy()
housing.plot(kind="scatter", x="longitude", y="latitude")
save_fig("bad_visualization_plot")


# In[23]:


# 데이터 이해하기
# 지리적 데이터 시각화

housing.plot(kind="scatter", x="longitude", y="latitude", alpha=0.1)
save_fig("better_visualization_plot")


# In[24]:


# 데이터 이해하기
# 중간 주택 가격과 다른 특성 사이의 상관관계

corr_matrix = housing.corr()
corr_matrix["median_house_value"].sort_values(ascending=False)


# In[25]:


# 데이터 이해하기
# 산점도 매트릭스로 상관관계 파악하기

from pandas.plotting import scatter_matrix
attributes = ["median_house_value", "median_income", "total_rooms", "housing_median_age"]
scatter_matrix(housing[attributes], figsize=(12,8))
save_fig("scatter_matrix_plot")


# In[26]:


# 특성 조합하기

housing["rooms_per_household"] = housing["total_rooms"]/housing["households"]
housing["bedrooms_per_room"]=housing["total_bedrooms"]/housing["total_rooms"]
housing["population_per_household"]=housing["population"]/housing["households"]
corr_matrix = housing.corr()
corr_matrix["median_house_value"].sort_values(ascending=False)


# In[27]:


# 데이터 준비
# 레이블과 데이터를 분리해서 가져오기

housing = strat_train_set.drop("median_house_value", axis=1)
housing_labels = strat_train_set["median_house_value"].copy()
sample_incomplete_rows = housing[housing.isnull().any(axis=1)].head()
sample_incomplete_rows


# In[28]:


# 데이터 준비
# 빈 데이터가 있을 때 정제 방법
# 해당 구역을 제거

sample_incomplete_rows.dropna(subset=["total_bedrooms"])


# In[29]:


# 데이터 준비
# 빈 데이터가 있을 때 정제 방법
# 해당 특성을 제거

sample_incomplete_rows.drop("total_bedrooms", axis = 1)


# In[30]:


# 데이터 준비
# 빈 데이터가 있을 때 정제 방법
# 특정 값으로 채움(0, 평균, 중간값 등)

median=housing["total_bedrooms"].median()
sample_incomplete_rows["total_bedrooms"].fillna(median, inplace=True)
print(sample_incomplete_rows)


# In[32]:


# 데이터 준비
# 빈 데이터가 있을 때 정제 방법
# 사이킷런의 SimpleImputer 사용하기

from sklearn.impute import SimpleImputer
imputer = SimpleImputer(strategy="median")
housing_num = housing.drop("ocean_proximity", axis=1)

imputer.fit(housing_num)
imputer.statistics_


# In[33]:


# 데이터 준비
# 빈 데이터가 있을 때 정제 방법
# 사이킷런의 SimpleImputer 사용하기

housing_num.median().values


# In[34]:


# 데이터 준비
# 빈 데이터가 있을 때 정제 방법
# 사이킷런의 SimpleImputer 사용하기

X = imputer.transform(housing_num)
housing_tr = pd.DataFrame(X, columns=housing_num.columns, index=housing_num.index)
housing_tr.loc[sample_incomplete_rows.index.values]


# In[35]:


# 데이터 준비
# 텍스트와 범주형 데이터 다루기

housing_cat = housing[["ocean_proximity"]]
housing_cat.head(10)


# In[36]:


# 데이터 준비
# 텍스트와 범주형 데이터 다루기
#사이킷런의 OrdinalEncoder

from sklearn.preprocessing import OrdinalEncoder
ordinal_encoder = OrdinalEncoder()
housing_cat_encoded = ordinal_encoder.fit_transform(housing_cat)
housing_cat_encoded[:10]


# In[37]:


# 데이터 준비
# 텍스트와 범주형 데이터 다루기
#사이킷런의 OrdinalEncoder

ordinal_encoder.categories_


# In[38]:


# 데이터 준비
# 데이터 준비
# 텍스트와 범주형 데이터 다루기

from sklearn.preprocessing import OneHotEncoder
cat_encoder = OneHotEncoder()
housing_cat_1hot = cat_encoder.fit_transform(housing_cat)
housing_cat_1hot.toarray()


# In[41]:


# 데이터 준비
# 나만의 데이터 정제기

# Sklearn.base에서 BaseEstimator, TransformerMixin을 가져온다.
from sklearn.base import BaseEstimator, TransformerMixin

#열 인덱스
rooms_ix, bedrooms_ix, population_ix, households_ix = 3, 4, 5, 6

# CombinedAttributesAdder 클래스 선언
# 매개변수: BaseEstimator, TransformerMixin
class CombinedAttributesAdder(BaseEstimator, TransformerMixin):
    
    # 초기화 메서드 선언
    # add_bedrooms_per_room = 하이퍼파리미터, 기본값 = True
    def __init__(self, add_bedrooms_per_room = True):
        # add_bedrooms_per_room을 자기 자신 add_bedrooms_per_room에 넣는다.
        self.add_bedrooms_per_room = add_bedrooms_per_room
        
    # fit 메서드 선언
    # 자기 자신을 반환한다.
    # 매개변수: self, X, y
    # X = imputer.transform(housing_num): 학습된 imputer 객체
    def fit(self, X, y=None):
        return self #아무것도 하지 않는다.
    
    # transform 메서드 선언
    # 매개 변수: self, X
    def transform(self, X):
        
        # 방 개수/ 가정수
        rooms_per_household = X[:, rooms_ix] / X[:, households_ix]
        # 인구 수/ 가정수
        population_per_household = X[:, population_ix] / X[:, households_ix]
        
        # 자기자신의 add_bedrooms_per_room이 있으면
        if self.add_bedrooms_per_room:
            
            # 침실 / 방 개수
            bedrooms_per_room = X[:, bedrooms_ix] / X[:, rooms_ix]
            # 1차원 배열을 칼럼으로 세로로 붙여서 2차원 배열 만들어서 반환
            return np.c_[X, rooms_per_household, population_per_household, bedrooms_per_room]
        
        else:
            # 1차원 배열을 칼럼으로 세로로 붙여서 2차원 배열 만들어서 반환
            return np.c_[X, rooms_per_household, population_per_household]

# CombinedAttributesAdder 클래스 생성
attr_adder = CombinedAttributesAdder(add_bedrooms_per_room=False)
# CombinedAttributesAdder 클래스의 transform 함수 호출
housing_extra_attribs = attr_adder.transform(housing.to_numpy())


# In[42]:


# 데이터 준비
# 수치형 파이프라인

from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler

num_pipeline = Pipeline([('imputer', SimpleImputer(strategy = "median")), ('attribs_adder', CombinedAttributesAdder()), ('std_scaler', StandardScaler()),])
housing_num_tr = num_pipeline.fit_transform(housing_num)
housing_num_tr


# In[43]:


# 데이터 준비
# 전체 파이프라인

from sklearn.compose import ColumnTransformer

num_attribs = list(housing_num)
cat_attribs = ["ocean_proximity"]

full_pipeline = ColumnTransformer([("num", num_pipeline, num_attribs), ("cat", OneHotEncoder(), cat_attribs),])
housing_prepared = full_pipeline.fit_transform(housing)

print(housing_prepared)
print(housing_prepared.shape)


# In[44]:


# 모델 선택과 훈련
# 훈련 세트에서 훈련하고 평가하기

from sklearn.linear_model import LinearRegression
lin_reg = LinearRegression()
lin_reg.fit(housing_prepared, housing_labels)


# In[45]:


# 모델 선택과 훈련
# 훈련 세트에서 훈련하고 평가하기
# 훈련 샘플 몇 개를 사용해 전체 파이프라인을 적용

some_data = housing.iloc[:5]
some_labels = housing_labels.iloc[:5]
some_data_prepared = full_pipeline.transform(some_data)
print("예측: ", lin_reg.predict(some_data_prepared))


# In[46]:


# 모델 선택과 훈련
# 훈련 세트에서 훈련하고 평가하기

print("레이블:", list(some_labels))


# In[47]:


# 모델 선택과 훈련
# 훈련 세트에서 훈련하고 평가하기

from sklearn.metrics import mean_squared_error

housing_predictions = lin_reg.predict(housing_prepared)
lin_mse = mean_squared_error(housing_labels, housing_predictions)
lin_rmse = np.sqrt(lin_mse)
lin_rmse


# In[48]:


# 모델 선택과 훈련
# 훈련 세트에서 훈련하고 평가하기

housing_labels.hist()


# In[49]:


# 모델 선택과 훈련
# 모델 변경하기

from sklearn.tree import DecisionTreeRegressor

tree_reg = DecisionTreeRegressor(random_state=42)
tree_reg.fit(housing_prepared, housing_labels)


# In[50]:


# 모델 선택과 훈련
# 모델 변경하기

housing_predictions = tree_reg.predict(housing_prepared)
tree_mse = mean_squared_error(housing_labels, housing_predictions)
tree_rmse = np.sqrt(tree_mse)
tree_rmse


# In[51]:


# 모델 선택과 훈련
# 교차검증을 사용한 평가

from sklearn.model_selection import cross_val_score

scores = cross_val_score(tree_reg, housing_prepared, housing_labels, scoring="neg_mean_squared_error", cv=10)
tree_rmse_scores = np.sqrt(-scores)


# In[52]:


# 모델 선택과 훈련
# 교차검증을 사용한 평가
# K-겹 교차검증: k 개의 서브셋으로 무작위로 분할 한 다음 결정 트리 모델을 10번 훈련하고 평가함

def display_scores(scores):
    print("점수:", scores)
    print("평균:", scores.mean())
    print("표준 편차:", scores.std())
    
display_scores(tree_rmse_scores)


# In[53]:


# 모델 선택과 훈련
# 교차검증을 사용한 평가
# K-겹 교차검증: k 개의 서브셋으로 무작위로 분할 한 다음 결정 트리 모델을 10번 훈련하고 평가함

lin_scores = cross_val_score(lin_reg, housing_prepared, housing_labels, scoring="neg_mean_squared_error", cv=10)
lin_rmse_scores = np.sqrt(-lin_scores)
display_scores(lin_rmse_scores)


# In[54]:


# 모델 선택과 훈련
# 모델 변경하기
# 앙상블 학습 모델인 랜덤 포레스트를 적용

from sklearn.ensemble import RandomForestRegressor

forest_reg = RandomForestRegressor(n_estimators=100, random_state=42)
forest_reg.fit(housing_prepared, housing_labels)


# In[55]:


# 모델 선택과 훈련
# 모델 변경하기
# 앙상블 학습 모델인 랜덤 포레스트를 적용

housing_predictions = forest_reg.predict(housing_prepared)
forest_mse = mean_squared_error(housing_labels, housing_predictions)
forest_rmse = np.sqrt(forest_mse)
forest_rmse


# In[57]:


# 모델 선택과 훈련
# 모델 변경하기
# 앙상블 학습 모델인 랜덤 포레스트를 적용

from sklearn.model_selection import cross_val_score
forest_scores = cross_val_score(forest_reg, housing_prepared, housing_labels, scoring="neg_mean_squared_error", cv=10)
forest_rmse_scores = np.sqrt(-forest_scores)
display_scores(forest_rmse_scores)


# In[60]:


# 모델 세부 튜닝
# 그리드 탐색

from sklearn.model_selection import GridSearchCV
param_grid = [
    
    #12(=3x4)개의 하이퍼파라미터 조합을 시도한다.
    {'n_estimators':[3, 10, 30], 'max_features': [2, 4, 6, 8]},
    
    # bootstrap은 False로 하고 6(=2ㅌ3)개의 조합을 시도한다.
    {'bootstrap': [False], 'n_estimators': [3, 10], 'max_features': [2, 3, 4]},]

forest_reg = RandomForestRegressor(random_state=42)

# 다섯 개의 폴드로 훈련하면 총 (12+6)*5=90 번의 훈련이 일어난다.
grid_search = GridSearchCV(forest_reg, param_grid, cv=5, scoring='neg_mean_squared_error', return_train_score=True)
grid_search.fit(housing_prepared, housing_labels)


# In[61]:


# 모델 세부 튜닝
# 그리드 탐색

print(grid_search.best_params_)
print(grid_search.best_estimator_)


# In[63]:


# 모델 세부 튜닝
# 그리드 탐색

pd.DataFrame(grid_search.cv_results_)


# In[65]:


# 모델 세부 튜닝
# 랜덤 탐색

from sklearn.model_selection import RandomizedSearchCV
from scipy.stats import randint

param_distribs = {
    'n_estimators': randint(low=1, high=200),
    'max_features': randint(low=1, high=8)
}

forest_reg = RandomForestRegressor(random_state=42)
rnd_search = RandomizedSearchCV(forest_reg, param_distributions=param_distribs, 
                                n_iter=10, cv=5, scoring='neg_mean_squared_error', random_state=42)
rnd_search.fit(housing_prepared, housing_labels)


# In[66]:


# 모델 세부 튜닝
# 랜덤 탐색

cvres = rnd_search.cv_results_
for mean_score, params in zip(cvres["mean_test_score"], cvres["params"]):
    print(np.sqrt(-mean_score), params)


# In[67]:


# 최종 모델 평가
# 특성 중요도와 결과

feature_importances = grid_search.best_estimator_.feature_importances_
feature_importances


# In[68]:


# 최종 모델 평가
# 특성 중요도와 결과

final_model = grid_search.best_estimator_

X_test = strat_test_set.drop("median_house_value", axis=1)
y_test = strat_test_set["median_house_value"].copy()

X_test_prepared = full_pipeline.transform(X_test)
final_predictions = final_model.predict(X_test_prepared)

final_mse = mean_squared_error(y_test, final_predictions)
final_rmse = np.sqrt(final_mse)
final_rmse


# In[72]:


# 최종 모델 평가
# 추정값의 정확도

from scipy import stats

confidence = 0.95
squared_errors = (final_predictions - y_test)**2
np.sqrt(stats.t.interval(confidence, len(squared_errors)-1, loc=squared_errors.mean(), scale=stats.sem(squared_errors)))


# In[73]:


# 최종 모델 평가
# 추정값의 정확도

m = len(squared_errors)
mean = squared_errors.mean()
tscore = stats.t.ppf((1+confidence)/2, df=m-1)
tmargin = tscore*squared_errors.std(ddof=1)/np.sqrt(m)
np.sqrt(mean-tmargin), np.sqrt(mean+tmargin)


# In[ ]:




