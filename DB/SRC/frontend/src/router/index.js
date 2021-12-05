import Vue from 'vue'
import VueRouter from 'vue-router'
import IndexPage from '@/components/IndexPage'
import EvalTodoView from '@/views/TodoListView'
import EvalEvaluatedView from '@/views/EvaluatedListView'
import EvalTaskEvalView from '@/views/EvalTaskEvalView'
import LoginPage from '@/components/main/Home'
import Submitter from '@/components/user/Submitter'
import GetTask from '@/components/user/GetTask'
import SubmitData from '@/components/user/SubmitData'
// 관리자 페이지
import AdminMain from '@/components/Admin/AdminMain'
import TaskCreate from '@/components/Admin/Task/Create/TaskCreate'
import ShowTaskInfo from '@/components/Admin/Task/Stat/ShowInfo'
import ShowTaskDetail from '@/components/Admin/Task/Stat/TaskView'
import ManagePage from '@/components/Admin/Task/Manage/TaskManage'
import TaskManage from '@/components/Admin/Task/Manage/ManageView'
import ShowMember from '@/components/Admin/Member/ShowMember'
import SearchMember from '@/components/Admin/Member/Search'
import UserInfo from '@/components/Admin/Member/UserInfo'
Vue.use(VueRouter)
import SignUpPage from '@/components/SignUpPage'
import ProfilePage from '@/components/ProfilePage'
import IntroPage from '@/components/Intro'

const router = new VueRouter({
  mode: 'history',
  routes: [
    {
      path: '/',
      name: 'IndexPage',
      component: IndexPage
    },
    {
      path: '/sign_up',
      name: 'SignUpPage',
      component: SignUpPage
    },
    {
      path: '/profile',
      name: 'ProfilePage',
      component: ProfilePage
    },
    {
      path: '/evaluator/:userID',
      redirect: '/evaluator/:userID/todo'
      // name: 'EvaluatorMainPage',
      // component: EvalTodoView
    },
    {
      path: '/evaluator/:userID/todo',
      name: 'EvaluatorTodoListPage',
      component: EvalTodoView
    },
    {
      path: '/evaluator/:userID/todo/:fileID',
      name: 'EvaluateTaskPage',
      component: EvalTaskEvalView
    },
    {
      path: '/evaluator/:userID/evaluated',
      name: 'EvaluatorEvaluatedPage',
      component: EvalEvaluatedView
    },
    {
      path: '/login',
      name: 'LoginPage',
      component: LoginPage
    },
    {
      path: '/submitter/:userID',
      name: 'Submitter',
      component: Submitter
    },
    {
      path: '/submitter/:userID/gettask',
      name: 'GetTask',
      component: GetTask
    },
    {
      path: '/submitter/:userID/submitdata',
      name: 'SubmitData',
      component: SubmitData
    },
    // 관리자 페이지 시작
    {
      path: '/admin',
      name: 'AdministratorMain',
      component: AdminMain
    },
    {
      path: '/admin/task/create',
      name: 'TaskCreate',
      component: TaskCreate
    },
    {
      path: '/admin/task/',
      redirect: '/admin/task/showall'
    },
    {
      path: '/admin/task/showall',
      name: 'ShowTaskInfo',
      component: ShowTaskInfo
    },
    {
      path: '/admin/task/showall/:taskName',
      name: 'ShowTaskDetail',
      component: ShowTaskDetail
    },
    {
      path: '/admin/task/manage',
      name: 'ManagePage',
      component: ManagePage
    },
    {
      path: '/admin/task/manage/:taskName',
      name: 'TaskManage',
      component: TaskManage
    },
    {
      path: '/admin/member/',
      redirect: '/admin/member/showlist'
    },
    {
      path: '/admin/member/showlist',
      name: 'ShowMember',
      component: ShowMember
    },
    {
      path: '/admin/member/search',
      name: 'SearchMember',
      component: SearchMember
    },
    {
      path: '/admin/:userID',
      name: 'UserInfo',
      component: UserInfo
    },
    // 관리자 페이지 끝
    {
      path: '/intro',
      name: 'Intro',
      component: IntroPage
    }
  ]
})
export default router;